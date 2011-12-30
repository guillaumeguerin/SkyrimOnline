/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline;

import com.skyrimonline.game.World;
import com.skyrimonline.game.WorldListener;
import com.skyrimonline.network.ServerListener;

/**
 *
 * @author yamashi
 */
public abstract class Script {
    
    private PluginManager manager = null;
    private WorldListener worldListener = null;
    private ServerListener serverListener = null;
    
    private long ptr;
    
    public enum Event{
        SERVER (1),
        WORLD  (2);
        
        private final int value;
        
        private Event(int value){
            this.value = value;
        }
        
        public int getValue(){
            return value;
        }
    }
    
    static {
        String curDir = System.getProperty("user.dir");
        System.load(curDir + "\\Script.dll");
    }
    
    protected void setWorldListener(WorldListener listener){
        worldListener = listener;
        manager.register(this, Event.WORLD);
    }
    
    protected void setServerListener(ServerListener listener){
        serverListener = listener;
        manager.register(this, Event.SERVER);
    }
    
    public void setPluginManager(PluginManager manager){
        this.manager = manager;
    }
    
    public void onNewShard(World world){
        if(serverListener != null)
            serverListener.onNewShard(world);
    }
    
    /**
     * Set the native pointer
     * @param ptr The native pointer
     */
    public void setPointer(long ptr){
        this.ptr = ptr;
    }
    
    public long getPointer(){
        return this.ptr;
    }
    
    public abstract void onEnable();
    public abstract void onDisable();

}
