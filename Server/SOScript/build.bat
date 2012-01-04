ECHO Generating JNI interface...
Echo com.skyrimonline.system.Log
javah -o ../Script/Src/System/LogJNI.h -classpath ../SOScript/build/classes com.skyrimonline.system.Log
Echo com.skyrimonline.game.World
javah -o ../Script/Src/Game/WorldJNI.h -classpath ../SOScript/build/classes com.skyrimonline.game.World
Echo com.skyrimonline.PluginManager
javah -o ../Script/Src/PluginManagerJNI.h -classpath ../SOScript/build/classes com.skyrimonline.PluginManager
Echo com.skyrimonline.network.Server
javah -o ../Script/Src/Network/ServerJNI.h -classpath ../SOScript/build/classes com.skyrimonline.network.Server
ECHO Done generating JNI interface !