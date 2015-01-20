/*---------------------------------------------------------------------------------------------
    Author       : ������

    Created Date : 2015-01-07

    Descriptions : ��Ƶ�ɼ�api 
  
    Version             Description             Date                Author
    0.1                 Created                 2015-01-07        ������

---------------------------------------------------------------------------------------------*/
#include "videodev2.h"
#include <fcntl.h>     
#include "typedef.h"
#include "debug.h"
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>


#define test 1

void *Video_Init()
{
	PVIDEO_INFO videoInfo = NULL;

	function_in();
	videoInfo = (PVIDEO_INFO)malloc(sizeof(VIDEO_INFO));
	videoInfo->fd = open("/dev/video0",O_RDWR);   

	function_out();
	return videoInfo;

}
int Video_SetConfig()
{
	int ret = 0;

	function_in();


	function_out();
	return ret;

}
int Video_GetConfig(void * vInst)
{
	int ret = 0;
	PVIDEO_INFO videoInfo = (PVIDEO_INFO)vInst;
	v4l2_capability *cap = &(videoInfo->videoCap);
	 v4l2_fmtdesc  *fmtdesc = &(videoInfo->videoFmt);     

	function_in();
 	ret = ioctl(videoInfo->fd, VIDIOC_QUERYCAP, cap);   //��ѯ�豸����
	if(ret < 0)
	{
		video_err("get videoCap failed![err %d]",ret);
		goto exit;
	}
  	video_dbg("Driver Name:%s\nCard Name:%s\nBus info:%s\nDriver Version:%u.%u.%u\n",  
            cap->driver,cap->card,cap->bus_info,(cap->version>>16)&0XFF, (cap->version>>8)&0XFF,cap->version&0XFF);    
   	fmtdesc->index=0;     
	fmtdesc->type=V4L2_BUF_TYPE_VIDEO_CAPTURE;     
#if test
	video_dbg("Support format:/n");     
	while(ioctl(videoInfo->fd,VIDIOC_ENUM_FMT,fmtdesc)!=-1)     //��ȡ��ǰ����֧�ֵ���Ƶ��ʽ
	{     
		video_dbg("/t%d.%s/n",fmtdesc->index+1,fmtdesc->description);     
		fmtdesc->index++;  
   	 }  

#endif	
	function_out();
exit: return ret;

}
int Video_GetFrame()
{
	int ret = 0;

	function_in();


	function_out();
	return ret;
}
int Video_Release(void * vInst)
{
	int ret = 0;
	PVIDEO_INFO videoInfo = (PVIDEO_INFO)vInst;

	function_in();
	close(videoInfo->fd);// �ر��豸     
	free(videoInfo);
	
	function_out();
	return ret;

}

