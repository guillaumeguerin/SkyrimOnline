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
   
   private long ptr;
   
   private native String getName(long ptr);
   private native int count(long ptr);
   
   public String getName(){
       return getName(ptr);
   }
   
   public int count(){
       return count(ptr);
   }
   
   /**
    * Set the native pointer
    * @param ptr The native pointer
    */
    public void setPointer(long ptr){
        this.ptr = ptr;
    }
}
