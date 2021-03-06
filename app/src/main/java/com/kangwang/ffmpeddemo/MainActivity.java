package com.kangwang.ffmpeddemo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.kangwang.ffmpeddemo.play.DNPlayer;

public class MainActivity extends AppCompatActivity {
    private DNPlayer player;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        SurfaceView surfaceView = findViewById(R.id.surfaceView);
        player = new DNPlayer();
        player.setSurfaceView(surfaceView);
        player.setDataSource("");
        player.prepare();
        player.setPrapare(new DNPlayer.OnPrepareListener() {
            @Override
            public void onPrepare() {
                System.out.println("播放器准备完成");
                start();
            }
        });
    }

    public void start(){
        player.start();
    }
}