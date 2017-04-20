package com.xinyue.passbook.utils;

import com.xinyue.passbook.R;

/**
 * Created by Administrator on 2017/3/23.
 */

public class NoteItemBgResources {
    private final static int [] BG_FIRST_RESOURCES = new int [] {
            R.drawable.list_yellow_up,
            R.drawable.list_blue_up,
            R.drawable.list_white_up,
            R.drawable.list_green_up,
            R.drawable.list_red_up
    };

    private final static int [] BG_NORMAL_RESOURCES = new int [] {
            R.drawable.list_yellow_middle,
            R.drawable.list_blue_middle,
            R.drawable.list_white_middle,
            R.drawable.list_green_middle,
            R.drawable.list_red_middle
    };

    private final static int [] BG_LAST_RESOURCES = new int [] {
            R.drawable.list_yellow_down,
            R.drawable.list_blue_down,
            R.drawable.list_white_down,
            R.drawable.list_green_down,
            R.drawable.list_red_down,
    };

    private final static int [] BG_SINGLE_RESOURCES = new int [] {
            R.drawable.list_yellow_single,
            R.drawable.list_blue_single,
            R.drawable.list_white_single,
            R.drawable.list_green_single,
            R.drawable.list_red_single
    };

    public static int getNoteBgFirstRes(int id) {
        return BG_FIRST_RESOURCES[id];
    }

    public static int getNoteBgLastRes(int id) {
        return BG_LAST_RESOURCES[id];
    }

    public static int getNoteBgSingleRes(int id) {
        return BG_SINGLE_RESOURCES[id];
    }

    public static int getNoteBgNormalRes(int id) {
        return BG_NORMAL_RESOURCES[id];
    }

}
