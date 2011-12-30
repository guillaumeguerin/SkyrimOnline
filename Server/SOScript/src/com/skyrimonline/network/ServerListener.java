/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline.network;

import com.skyrimonline.game.World;

/**
 *
 * @author yamashi
 */
public interface ServerListener {
    public void onNewShard(World world);
    public void onDeleteShard(World world);
}
