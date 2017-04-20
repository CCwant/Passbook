package com.xinyue.passbook.ui.adapter;

import android.content.Context;
import android.text.format.DateUtils;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.TextView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.base.SimpleBaseAdapter;
import com.xinyue.passbook.entity.Note;
import com.xinyue.passbook.utils.NoteItemBgResources;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;

/**
 * Created by Administrator on 2017/3/22.
 */

public class ContentAdapter extends SimpleBaseAdapter<Note> {

    private HashMap<Integer, Boolean> mSelectedIndex;
    private boolean mChoiceMode;
    public ContentAdapter(Context context) {
        super(context);
        mSelectedIndex = new HashMap<Integer, Boolean>();
    }
    @Override
    public void addAll(List<Note> datas) {
        super.addAll(datas);
    }

    int bgId=0;
    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        ViewHolder viewHolder=null;
        if(convertView == null){
            viewHolder=new ViewHolder();
            convertView= LayoutInflater.from(context).inflate(R.layout.item_book,parent,false);
            viewHolder.txtTitle=(TextView)convertView.findViewById(R.id.txt_title);
            viewHolder.txtTime=(TextView)convertView.findViewById(R.id.txt_time);
            viewHolder.chbSelect=(CheckBox)convertView.findViewById(R.id.chb_select);
            convertView.setTag(viewHolder);
        }else{
            viewHolder=(ViewHolder)convertView.getTag();
        }

        final Note book=datas.get(position);
        viewHolder.txtTitle.setText(book.getTitle());
        viewHolder.txtTime.setText(DateUtils.getRelativeTimeSpanString(book.getModifyTime()));

        final boolean checked=isSelectedItem(position);
        if(mChoiceMode){
            viewHolder.chbSelect.setVisibility(View.VISIBLE);
            viewHolder.chbSelect.setChecked(checked);
        }else{
            viewHolder.chbSelect.setVisibility(View.GONE);
        }




        if(position != getCount()-1){
            convertView.setBackgroundResource(NoteItemBgResources.getNoteBgNormalRes(bgId));
        }else {
            convertView.setBackgroundResource(NoteItemBgResources.getNoteBgLastRes(bgId));
        }




            return convertView;
    }
    class ViewHolder{
        TextView txtTitle;
        TextView txtTime;
        CheckBox chbSelect;

    }
    public void selectAll(boolean checked) {
        for (int i = 0; i < getCount(); i++) {
            setCheckedItem(i, checked);
        }
    }
    public boolean isAllSelected() {
        int checkedCount = getSelectedCount();
        return (checkedCount != 0 && checkedCount == getCount());
    }
    public int getSelectedCount() {
        Collection<Boolean> values = mSelectedIndex.values();
        if (null == values) {
            return 0;
        }
        Iterator<Boolean> iter = values.iterator();
        int count = 0;
        while (iter.hasNext()) {
            if (true == iter.next()) {
                count++;
            }
        }
        return count;
    }


    public boolean isInChoiceMode() {
        return mChoiceMode;
    }

    public void setChoiceMode(boolean mode) {
        mSelectedIndex.clear();
        mChoiceMode = mode;
    }

    public void setCheckedItem(final int position, final boolean checked) {
        mSelectedIndex.put(position, checked);
        notifyDataSetChanged();
    }
    public boolean isSelectedItem(final int position) {
        if (null == mSelectedIndex.get(position)) {
            return false;
        }
        return mSelectedIndex.get(position);
    }

    public HashSet<Integer> getSelectedItemIds() {
        HashSet<Integer> itemSet = new HashSet<Integer>();
        for (Integer position : mSelectedIndex.keySet()) {
            if (mSelectedIndex.get(position) == true) {
                //Book book = getItem(position);
                itemSet.add(position);
            }
        }
        return itemSet;
    }
    public void removeSelectedItems(){
        for (Integer position : mSelectedIndex.keySet()) {
            if (mSelectedIndex.get(position) == true) {
                datas.remove(position);
            }
        }
        notifyDataSetChanged();
    }

}
