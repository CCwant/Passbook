package com.xinyue.passbook.entity;

import android.os.Parcel;
import android.os.Parcelable;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.Collection;

/**
 * Created by Administrator on 2017/3/27.
 */
public class Note implements Parcelable{
    private String title;
    private String text;
    private long modifyTime;

    public Note(){

    }
    protected Note(Parcel in) {
        title = in.readString();
        text = in.readString();
        modifyTime = in.readLong();
    }
    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(title);
        dest.writeString(text);
        dest.writeLong(modifyTime);
    }
    @Override
    public int describeContents() {
        return 0;
    }
    public static final Creator<Note> CREATOR = new Creator<Note>() {
        @Override
        public Note createFromParcel(Parcel in) {
            return new Note(in);
        }
        @Override
        public Note[] newArray(int size) {
            return new Note[size];
        }
    };

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getText() {
        return text;
    }

    public void setText(String text) {
        this.text = text;
    }

    public long getModifyTime() {
        return modifyTime;
    }

    public void setModifyTime(long modifyTime) {
        this.modifyTime = modifyTime;
    }

    public JSONObject getTextByJson(){
        JSONObject jsb=new JSONObject();
        try {
            jsb.put("text",text);
            jsb.put("modifytime",modifyTime);
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return jsb;
    }
    public void parseText(String text){
        try {
            JSONObject jsb=new JSONObject(text);
            setText(jsb.getString("text"));
            setModifyTime(jsb.getLong("modifytime"));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String toString() {
        return "Note{" +
                "title='" + title + '\'' +
                ", text='" + text + '\'' +
                ", modifyTime=" + modifyTime +
                '}';
    }
}
