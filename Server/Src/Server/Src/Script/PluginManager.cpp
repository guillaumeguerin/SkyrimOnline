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
		void PluginManager::Initialize()
		{
			boost::filesystem::path lDir(".");

			if(!boost::filesystem::exists(lDir))
				boost::filesystem::create_directory(lDir);

			std::vector<boost::filesystem::path> lFiles;

			std::copy(boost::filesystem::directory_iterator(lDir),boost::filesystem::directory_iterator(),std::back_inserter(lFiles));

			JavaManager::ClassPath lPath;
			for(auto it = lFiles.begin(); it != lFiles.end(); it++)
			{
				if(it->extension() == ".jar")
				{
					lPath.push_back((*it).string());
				}
			}

			mJava = new JavaManager(lPath);

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
					mPlugins.push_back(std::make_tuple(new JavaPlugin(it->string(), *mJava), it->filename().string()));
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
	}
}