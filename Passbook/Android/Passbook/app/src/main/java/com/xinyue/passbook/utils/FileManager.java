package com.xinyue.passbook.utils;


import java.io.File;
import java.io.IOException;

/**
 * 文件管理类
 * Created by ccwant on 2016/09/13 09:26
 */
public class FileManager {

	public static final String FILE_PATH="xinyue/passbook/";

	/**
	 * 获取APP文件通一保存目录
	 * @return
     */
	public static String getSaveFilePath() {
		final String path = CommonUtil.getRootFilePath() + FILE_PATH;
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	public static boolean isPasswdFileExists() {
		File file = readPasswdFile();
		if (file.exists()) {
			return true;
		}
		return false;
	}
	public static File readPasswdFile(){
		final String path = getSaveFilePath() + "book.passwd";
		return new File(path);
	}
	public static File createPasswdFile(){
		final String path = getSaveFilePath()+"book.passwd";
		File file = new File(path);
		if (!file.exists()) {
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return file;
	}


	/**
	 * 获取图片缓存目录
	 * @return
     */
	public static String getImageCachePath(){
		final String path = getSaveFilePath()+"image";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取文件上传的缓存目录，上传完删除文件
	 * @return
     */
	public static String getFileUploadCachePath(){
		final String path = getSaveFilePath()+"FileTemp";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取日志缓存目录
	 * @return
     */
	public static String getLogCachePath(){
		final String path = getSaveFilePath()+"xlog";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取语音保存目录
	 * @return
     */
	public static String getSaveVoicePath() {
		final String path = getSaveFilePath() + "voice";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取图片保存目录
	 * @return
     */
	public static String getSaveImagePath() {
		final String path = getSaveFilePath() + "picture";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 导出文件目录
	 * @return
     */
	public static String getExportPath() {
		final String path = getSaveFilePath() + "export";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取视频保存目录
	 * @return
     */
	public static String getSaveVideoPath() {
		final String path = getSaveFilePath() + "video";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}

	/**
	 * 获取视频缓存目录
	 * @return
     */
	public static String getSaveVideoTempPath() {
		final String path = getSaveFilePath() + "video/temp";
		File file = new File(path);
		if (!file.exists()) {
			file.mkdirs();
		}
		return path;
	}
}
