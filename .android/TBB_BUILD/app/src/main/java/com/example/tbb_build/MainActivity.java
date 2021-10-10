package com.example.tbb_build;

import static org.libsdl.app.SDLActivity.getNativeSurface;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Surface;
import android.view.View;
import android.widget.TextView;
import org.libsdl.app.SDLActivity;


public class MainActivity extends SDLActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("main");




    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
       // SDLActivity.nativeRunMain("libmain.so", "SDL_main", new int[2]);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}