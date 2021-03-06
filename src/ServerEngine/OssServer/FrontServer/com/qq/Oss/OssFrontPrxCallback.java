// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 2.1.5.0 by WSRD Tencent.
// Generated from `FrontServer.jce'
// **********************************************************************

package com.qq.Oss;

public abstract class OssFrontPrxCallback extends com.qq.taf.proxy.ServantProxyCallback
{
    protected String __Oss__OssFront_all[] = 
    {
        "doOssRequest"
    };

    protected String sServerEncoding = "GBK";
    public int setServerEncoding(String se){
        sServerEncoding = se;
        return 0;
    }

    public abstract void callback_doOssRequest(int _ret, String strRetData);

    public abstract void callback_doOssRequest_exception(int _iRet);

    final public int _onDispatch(String sFuncName, com.qq.taf.ResponsePacket response)
    {

        int iPos = java.util.Arrays.binarySearch(__Oss__OssFront_all, sFuncName);
        if(iPos < 0 || iPos >= 1) return -1; //or throw execption?
        switch(iPos)
        {
            case 0:
            {
                if ( response.iRet != com.qq.taf.cnst.JCESERVERSUCCESS.value )
                {
                    callback_doOssRequest_exception(response.iRet);
                    return response.iRet;
                }
                com.qq.taf.jce.JceInputStream _is = new com.qq.taf.jce.JceInputStream(response.sBuffer);
                _is.setServerEncoding(sServerEncoding);
                int _ret = 0;
                _ret = (int) _is.read(_ret, 0, true);

                String strRetData = "";
                strRetData = (String) _is.read(strRetData, 2, true);

                callback_doOssRequest(_ret, strRetData);
                break;
            }
        }
        return 0;
    }
}
