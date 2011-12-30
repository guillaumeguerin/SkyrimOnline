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
public class SkyScript extends Script {
    
    private TestServer server = new TestServer();
   
    public static void main(String[] args)
    {
    }

    @Override
    public void onEnable() {
        setServerListener(server);
        Log.getInstance().Debug("SkyScript loaded");
    }

    @Override
    public void onDisable() {
        Log.getInstance().Debug("SkyScript disabled");
    }
}
