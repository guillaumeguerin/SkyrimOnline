#include "stdafx.h"
#include <Script/Plugin.h>
#include <Script/javaPlugin.h>
#include <Script/PluginManager.h>
#include <boost/filesystem.hpp>

namespace Skyrim
{
	namespace Script
	{
		//---------------------------------------------------------------------------------------
		PluginManager* PluginManager::mInstance = nullptr;
		//---------------------------------------------------------------------------------------
		PluginManager& PluginManager::GetInstance()
		{
			if(mInstance == nullptr)
			{
				mInstance = new PluginManager;
				mInstance->Initialize();
			}
			return *mInstance;
		}
		//---------------------------------------------------------------------------------------
		void PluginManager::Initialize()
		{
			boost::filesystem::path lDir("./Script");

			if(!boost::filesystem::exists(lDir))
				boost::filesystem::create_directory(lDir);

			std::vector<boost::filesystem::path> lFiles;

			std::copy(boost::filesystem::directory_iterator(lDir),boost::filesystem::directory_iterator(),std::back_inserter(lFiles));

			JavaManager::ClassPath lPath;
			lPath.push_back("./SOScript.jar");
			for(auto it = lFiles.begin(); it != lFiles.end(); it++)
			{
				if(it->extension() == ".jar")
				{
					lPath.push_back((*it).string());
				}
			}

			mJava = new JavaManager(lPath);
			mPluginManager = new JavaPluginManager(*mJava,*this);

			for(auto it = lFiles.begin(); it != lFiles.end(); it++)
			{
				if(it->extension() == ".dll")
				{
					HMODULE lDll = LoadLibraryA((*it).string().c_str());
					if(lDll != NULL)
					{
						typedef Plugin* (*RegisterScripts)();
						RegisterScripts pfnLoad = (RegisterScripts)GetProcAddress( lDll, "LoadPlugin");

						if(pfnLoad)
						{
							mPlugins.push_back(std::make_tuple(pfnLoad(), it->filename().string()));
							mSharedObjects.push_back(lDll);
						}
						else
						{
							FreeLibrary(lDll);
							System::Log::GetInstance()->Error(std::string("Could not load [" + it->filename().string() + "] the LoadPlugin function was not found") );
						}
					}
					else
					{
						System::Log::GetInstance()->Error(std::string("Could not load [%s] no idea why") + it->filename().string());
					}
				}
				else if(it->extension() == ".jar")
				{
					mPlugins.push_back(std::make_tuple(new JavaPlugin(it->string(), *mJava, *mPluginManager), it->filename().string()));
				}
			}

			for(auto it = mPlugins.begin(); it != mPlugins.end(); it++)
			{
				std::get<0>(*it)->OnEnable();
			}
		}
		//---------------------------------------------------------------------------------------
		void PluginManager::Free()
		{
			for(auto it = mPlugins.begin(); it != mPlugins.end(); it++)
			{
				std::get<0>(*it)->OnDisable();
			}

			for(auto it = mSharedObjects.begin(); it != mSharedObjects.end(); it++)
			{
				FreeLibrary(*it);
			}
		}
		//---------------------------------------------------------------------------------------
		void PluginManager::AddShard(Game::IWorld* world)
		{
			world->CreateJava();

			for(auto it = mServerListeners.begin(); it != mServerListeners.end(); it++)
			{
				 (*it)->OnNewShard(world);
			}
		}
		//---------------------------------------------------------------------------------------
		void PluginManager::Register(Plugin* plugin, int event)
		{
			switch(event)
			{
				case SERVER: mServerListeners.push_back(plugin); break;
				case WORLD: mWorldListeners.push_back(plugin); break;
			}
		}
		//---------------------------------------------------------------------------------------
		JavaManager& PluginManager::GetJavaManager()
		{
			return *mJava;
		}
		//---------------------------------------------------------------------------------------
	}
}