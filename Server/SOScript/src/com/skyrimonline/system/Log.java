/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline.system;

/**
 *
 * @author yamashi
 */
public class Log {
    
    private static Log instance = new Log();
    
    public native void Debug(String pToLog);
    public native void Error(String pToLog);
    public native void Print(String pToLog);
    
    private Log(){
        
    }
    
    public static Log getInstance()
    {
        return instance;
    }
}
