/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.skyrimonline;

import com.skyrimonline.game.World;
import com.skyrimonline.network.ServerListener;
import com.skyrimonline.system.Log;

/**
 *
 * @author yamashi
 */
public class TestServer implements ServerListener {

    @Override
    public void onNewShard(World world) {
        Log.getInstance().Debug("SkyScript got a new World instance : " + world.getName());
    }

    @Override
    public void onDeleteShard(World world) {
    }
    
}
