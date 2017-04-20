package com.xinyue.passwd.data;



import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.xinyue.passwd.Content;
import com.xinyue.passwd.utils.ByteUtils;
import com.xinyue.passwd.io.ByteBuffer;


public class MapListData implements IData{

	private int count=0; 
	private List<MapItem> list=new ArrayList<MapItem>();
	public MapListData() {
		
	}
	public MapListData(byte[] data) {
		ByteBuffer buffer=new ByteBuffer(data);
		//--------
		byte[] data1=buffer.read(4);
		this.count=(int)ByteUtils.bytesToInt32(data1);
		//--------
		for (int i = 0; i <  this.count; i++) {
			byte[] data2=buffer.read(4);
			int size=(int) ByteUtils.bytesToInt32(data2);
			//--------
			byte[] data3=buffer.read(size);
			MapItem item=new MapItem(data3);
			list.add(item);
		}
	}
	public void add(byte[] typeName,byte[] text)
	{
		MapItem item = createMapItem(typeName,text);	
		if(list.add(item)){
			count++;
		};
	}
	public void update(int index,byte[] typeName,byte[] text){
		MapItem item = createMapItem(typeName,text);	
		list.set(index, item);
	}
	public void remove(int index){
		list.remove(index);
		count--;
	}
	public int count(){
		return count;
	}
	@Override
	public int length(){
		int length=4;
		for (int i = 0; i < count; i++) {
			MapItem item=list.get(i);
			length+=item.length();
		}
		return length;
	}
	public List<Content> getData(){
		List<Content> contents=new ArrayList<Content>();
		for (int i = 0; i < count; i++) {
			MapItem item=list.get(i);
			Content content=new Content();
			content.setTypeName(item.text.typeName);
			content.setText(item.text.text);
			contents.add(content);
		}
		return contents;
	}
	@Override
	public byte[] getValue(){
		byte[] data=new byte[length()];
		int offset=0;
		byte[] data1=ByteUtils.int32ToBytes(count);
		System.arraycopy(data1, 0,data,0,4);
		offset+=4;
		for (int i = 0; i < count; i++) {
			MapItem item=list.get(i);
			System.arraycopy(item.getValue(), 0,data,offset,item.length());
			offset+=item.length();
		}
		return data;
	}
	
	
	
	private TextItem createTextItem(byte[] typeName,byte[] text){
		TextItem data=new TextItem();
		data.typeName=typeName;
		data.typeNameLen=typeName.length;
		data.text=text;
		data.textLen=text.length;
		return data;
	}
	private MapItem createMapItem(byte[] typeName,byte[] text){
		TextItem data=createTextItem(typeName,text);
		MapItem item=new MapItem();
		item.size=data.length();
		item.text=data;
		return item;
	}
	private class MapItem implements IData{
		private int size;//数据段的长度，不包括自己
		private TextItem text;
		
		public MapItem(){
			
		}
		public MapItem(byte[] data){
			text=new TextItem();
			size=data.length;
			ByteBuffer buffer=new ByteBuffer(data);
			//--------------
			byte[] data1=buffer.read(4);
			text.typeNameLen=(int) ByteUtils.bytesToInt32(data1);
			//--------------
			byte[] data2=buffer.read(text.typeNameLen);
			text.typeName=data2;
			//--------------
			byte[] data3=buffer.read(4);
			text.textLen=(int) ByteUtils.bytesToInt32(data3);
			//--------------
			byte[] data4=buffer.read(text.textLen);
			text.text=data4;
		}
		@Override
		public int length(){
			return text.length()+4;
		}
		@Override
		public byte[] getValue(){
			byte[] data=new byte[length()];
			byte[] data1=ByteUtils.int32ToBytes(size);
			System.arraycopy(data1, 0,data,0,4);
			System.arraycopy(text.getValue(), 0,data,4,text.length());
			return data;
		}
		
	}
	private class TextItem implements IData{
		private int typeNameLen; 
		private byte[] typeName;
		private int textLen; 
		private byte[] text;
		

		@Override
		public int length(){
			return typeNameLen+textLen+8;
		}
		@Override
		public byte[] getValue(){
			byte[] data=new byte[length()];
			byte[] data1=ByteUtils.int32ToBytes(typeNameLen);
			byte[] data2=ByteUtils.int32ToBytes(textLen);
			System.arraycopy(data1, 0,data,0,4);
			System.arraycopy(typeName, 0,data,4,typeNameLen);
			System.arraycopy(data2, 0,data,typeNameLen+4,4);
			System.arraycopy(text, 0,data,typeNameLen+8,textLen);
			return data;
		}
	}
	
}
