package com.xinyue.passbook.ui;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.ActionMode;
import android.view.HapticFeedbackConstants;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;

import com.xinyue.passbook.R;
import com.xinyue.passbook.entity.Note;
import com.xinyue.passbook.ui.adapter.ContentAdapter;
import com.xinyue.passbook.base.XSupportActivity;
import com.xinyue.passbook.utils.PasswdUtils;

import java.util.Comparator;
import java.util.List;

public class MainActivity extends XSupportActivity {


    private ListView mLstContent;
    private ContentAdapter mAdapter;

    ModeCallback mModeCallback;
    public static void jumpTo(Context context){
        Intent intent=new Intent(context,MainActivity.class);
        context.startActivity(intent);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("Passbook");
        stringFromJNI();

        mModeCallback=new ModeCallback();
        mAdapter=new ContentAdapter(this);
        mLstContent=(ListView)findViewById(R.id.lst_content);
        mLstContent.setAdapter(mAdapter);
        mLstContent.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Note book=mAdapter.getItem(position);
                Log.e("123","book:"+book.toString());

                if (mAdapter.isInChoiceMode()) {
                    mModeCallback.onItemCheckedStateChanged(null, position, id,!mAdapter.isSelectedItem(position));
                    return;
                }
                BookActivity.jumpTo(MainActivity.this,position,book);

            }
        });
        mLstContent.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                Note book=mAdapter.getItem(position);
                if(!mAdapter.isInChoiceMode()){
                    if (mLstContent.startActionMode(mModeCallback) != null) {
                        mModeCallback.onItemCheckedStateChanged(null, position, id, true);
                        mLstContent.performHapticFeedback(HapticFeedbackConstants.LONG_PRESS);
                    }
                }
                return true;
            }
        });
    }
    private void loadData(){
        List<Note> books=getAppInterface().getNotes();
        mAdapter.addAll(books);
    }
    private void refreshData(){
        if(mAdapter.getCount()>0){
            mAdapter.clear();
        }
        loadData();
    }
    private void batchDelete(){
        showProgressDialog();
        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                for (int position : mAdapter.getSelectedItemIds()) {
                    getAppInterface().removeNote(position);
                    mAdapter.remove(position);
                }
                PasswdUtils.export(getAppInterface());
                mModeCallback.finishActionMode();
                dismissProgressDialog();
            }
        },500);
    }



    @Override
    protected void onResume() {
        super.onResume();
        refreshData();
    }



    private class ModeCallback implements ListView.MultiChoiceModeListener, MenuItem.OnMenuItemClickListener {
        private ActionMode mActionMode;
        private Button mBtnSelectMenu;
        private Button mBtnSelectAll;
        private ImageView mImgSelectDelete;

        @Override
        public void onItemCheckedStateChanged(ActionMode mode, int position, long id, boolean checked) {
            mAdapter.setCheckedItem(position, checked);
            updateMenu();
        }
        @Override
        public boolean onCreateActionMode(ActionMode mode, Menu menu) {
            //这个地方有坑

            mActionMode = mode;
            mAdapter.setChoiceMode(true);
            mLstContent.setLongClickable(false);

            View customView = LayoutInflater.from(MainActivity.this).inflate(R.layout.note_list_dropdown_menu, null);
            mode.setCustomView(customView);
            mBtnSelectMenu=(Button)customView.findViewById(R.id.selection_menu);

            //全选
            mBtnSelectAll=(Button)customView.findViewById(R.id.selection_all);
            mBtnSelectAll.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mAdapter.isAllSelected()) {
                        mAdapter.selectAll(false);
                    } else {
                        mAdapter.selectAll(true);
                    }
                    updateMenu();
                }
            });
            //
            mImgSelectDelete=(ImageView)customView.findViewById(R.id.selection_delete);
            mImgSelectDelete.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    if (mAdapter.getSelectedCount() == 0) {
                        showToast("没有选择");
                        return ;
                    }
                    AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                    builder.setTitle(getString(R.string.alert_title_delete));
                    builder.setIcon(android.R.drawable.ic_dialog_alert);
                    builder.setMessage(getString(R.string.alert_message_delete_notes, mAdapter.getSelectedCount()));
                    builder.setPositiveButton(android.R.string.ok, new DialogInterface.OnClickListener() {
                        public void onClick(DialogInterface dialog, int which) {
                            batchDelete();
                        }
                    });
                    builder.setNegativeButton(android.R.string.cancel, null);
                    builder.show();
                }
            });
            return true;
        }

        @Override
        public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
            return false;
        }

        @Override
        public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
            return false;
        }

        @Override
        public void onDestroyActionMode(ActionMode mode) {
            mAdapter.setChoiceMode(false);
            mLstContent.setLongClickable(true);
            mAdapter.notifyDataSetChanged();
        }
        @Override
        public boolean onMenuItemClick(MenuItem item) {
           return false;
        }
        public void finishActionMode() {
            mActionMode.finish();
        }

        private void updateMenu() {
            int selectedCount = mAdapter.getSelectedCount();
            // Update dropdown menu
            String format = getResources().getString(R.string.menu_select_title, selectedCount);
            mBtnSelectMenu.setText(format);

            if (mAdapter.isAllSelected()) {
                //取消
                mBtnSelectAll.setText(R.string.menu_deselect_all);
            } else {
                //选择
                mBtnSelectAll.setText(R.string.menu_select_all);
            }
        }
    }








    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
}

