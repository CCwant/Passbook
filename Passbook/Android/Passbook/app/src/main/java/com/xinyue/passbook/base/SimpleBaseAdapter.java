package com.xinyue.passbook.base;

import android.content.Context;
import android.util.Log;
import android.widget.BaseAdapter;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;


/**
 * 简单的BaseAdapter的封装
 * Created by ccwant on 2016/9/23.
 */
public abstract class SimpleBaseAdapter<T> extends BaseAdapter {
    protected String TAG=getClass().getSimpleName();
    private final Object mLock = new Object();
    protected Context context;
    protected List<T> datas = new ArrayList<T>();


    public SimpleBaseAdapter(Context context){
        this.context=context;
    }

    /**
     * 清理数据,并通知
     */
    public void clear() {
        this.datas.clear();
        notifyDataSetChanged();
    }

    @Override
    public void notifyDataSetChanged() {
        super.notifyDataSetChanged();
    }

    /**
     * 只清理数据
     */
    public void onlyClear() {
        this.datas.clear();
    }

    /**
     * 更新指定位置的数据
     * @param location
     * @param data
     */
    public void update(int location,T data){
        this.datas.set(location,data);
        notifyDataSetChanged();
    }
    public void insert(int index,T data) {
        synchronized (mLock) {
            this.datas.add(index, data);
        }
        notifyDataSetChanged();
    }
    public void addAll(int location, Collection<? extends T> collection){
        synchronized (mLock) {
            this.datas.addAll(location, collection);
        }
        notifyDataSetChanged();
    }
    /**
     * 添加所有数据到集合，并通知
     * @param datas
     */
    public void addAll(List<T> datas) {
        if(datas==null){
            return;
        }
        this.datas.addAll(datas);
        notifyDataSetChanged();
    }
    public void addAll(Collection<? extends T> collection) {
        synchronized (mLock) {
            datas.addAll(collection);
        }
        notifyDataSetChanged();
    }
    public void addAll(T ... items) {
        synchronized (mLock) {
            Collections.addAll(datas, items);
        }
        notifyDataSetChanged();
    }
    /**
     * 添加数据到集合，并通知
     * @param data
     */
    public void add(T data){
        this.datas.add(data);
        notifyDataSetChanged();
    }

    /**
     * 移除指定位置数据
     * @param position
     */
    public void remove(int position){
        this.datas.remove(position);
        notifyDataSetChanged();
    }

    public void sort(Comparator<? super T> comparator) {
        synchronized (mLock) {
            Collections.sort(datas, comparator);
        }
        notifyDataSetChanged();
    }
    /**
     * 获取数据
     * @return
     */
    public List<T> getData(){
        return this.datas;
    }

    @Override
    public int getCount() {
        return datas.size();
    }

    @Override
    public T getItem(int position) {
        return datas.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }



}
