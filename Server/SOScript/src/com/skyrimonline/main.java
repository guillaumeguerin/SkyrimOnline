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
public class main implements Script {

    static {
        String curDir = System.getProperty("user.dir");
        System.load(curDir + "\\Script.dll");
    }
    
    public static void main(String[] args)
    {
    
    }
    
    main(){
        
    }


    @Override
    public void onEnable() {
        Log.getInstance().Debug("Main script loaded");
    }

    @Override
    public void onDisable() {
        Log.getInstance().Debug("Main script disabled");
    }
}
