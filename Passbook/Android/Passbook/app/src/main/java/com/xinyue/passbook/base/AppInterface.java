package com.xinyue.passbook.base;

import android.content.Context;

import com.xinyue.passbook.entity.Note;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

/**
 * Created by Administrator on 2017/3/23.
 */

public class AppInterface {

    final Context mContext;
    String password;
    List<Note> notes=new ArrayList<>();
    public AppInterface(Context context){
        mContext = context;
    }

    public void addNote(Note note){
        notes.add(note);
    }
    public void clearNote(){
        notes.clear();
    }
    public void addNote(List<Note> notes){
        notes.addAll(notes);
    }
    public void updateNote(int index,Note note){
        notes.set(index,note);
    }
    public void removeNote(int index){
        notes.remove(index);
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<Note> getNotes() {
        Collections.sort(notes, new Comparator<Note>() {
            @Override
            public int compare(Note o1, Note o2) {
                if(o1.getModifyTime() > o2.getModifyTime()){
                    return -1;
                }else if(o1.getModifyTime() < o2.getModifyTime()){
                    return 1;
                }else {
                    return 0;
                }
            }
        });
        return notes;
    }
}
