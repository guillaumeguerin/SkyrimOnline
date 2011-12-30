/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline;

import com.skyrimonline.system.Log;

/**
 *
 * @author yamashi
 */
public class PluginManager {
    
    private long ptr;
    
    static {
        String curDir = System.getProperty("user.dir");
        System.load(curDir + "\\Script.dll");
    }
    
    /**
     * Private native impl of register
     * @param ptr Native pointer
     * @param event The event to register
     */
    private native void register(long ptr, long scriptPtr, int event);
    
    public void register(Script script, Script.Event event){
        register(ptr, script.getPointer(), event.getValue());
    }
        
    /**
     * Set the native pointer
     * @param ptr The native pointer
     */
    public void setPointer(long ptr){
        this.ptr = ptr;
        Log.getInstance().Debug(this.getClass().getCanonicalName() + " instanciated !");
    }
}
