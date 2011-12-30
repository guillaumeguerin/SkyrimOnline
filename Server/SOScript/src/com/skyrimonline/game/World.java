/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline.game;

/**
 *
 * @author yamashi
 */
public class World {
    
   private native String GetName(long ptr);
   private native int Count(long ptr);
}
