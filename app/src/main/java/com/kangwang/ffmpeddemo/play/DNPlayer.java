package com.kangwang.ffmpeddemo.play;

import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.NonNull;

public class DNPlayer implements SurfaceHolder.Callback {
    private String sourceData;
    private SurfaceHolder holder;
    private OnPrepareListener prepareListener;

    public void setSurfaceView(SurfaceView surfaceView) {
        holder = surfaceView.getHolder();
        holder.addCallback(this);
    }

    public void setDataSource(String sourceData) {
        this.sourceData = sourceData;
    }

    public void prepare() {
        native_prepare(sourceData);
    }

    public void start(){
        native_start();
    }

    public void realse(){
        holder.removeCallback(this);
    }

    @Override
    public void surfaceCreated(@NonNull SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(@NonNull SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(@NonNull SurfaceHolder holder) {

    }

    native void native_prepare(String sourceData);

    native void native_start();

    public void onError(int errorCode){

    }

    public void onPrepare(){
        if (prepareListener!=null){
            prepareListener.onPrepare();
        }
    }

    public void setPrapare(OnPrepareListener prepareListener){
        this.prepareListener = prepareListener;
    }

    public interface OnPrepareListener{
        void onPrepare();
    }
}
