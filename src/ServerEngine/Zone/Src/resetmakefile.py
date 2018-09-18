#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Date    : 2017-12-28 16:28:50
# @Author  : Your Name (you@example.org)
# @Link    : http://example.org
# @Version : $Id$

import os,sys

import json
# import timetool

if sys.version_info > (3,0):
    def cmp(a,b):
        import operator
        return operator.eq(a,b)


#获取脚本路径
def cur_file_dir():
    pathx = sys.argv[0]
    tmppath,_file = os.path.split(pathx)
    if cmp(tmppath,'') == 0:
        tmppath = sys.path[0]
    #判断为脚本文件还是py2exe编译后的文件，如果是脚本文件，则返回的是脚本的目录，如果是py2exe编译后的文件，则返回的是编译后的文件路径
    if os.path.isdir(tmppath):
        return tmppath
    elif os.path.isfile(tmppath):
        return os.path.dirname(tmppath)
    
#获取父目录
def GetParentPath(strPath):
    if not strPath:
        return None;
    lsPath = os.path.split(strPath);
    if lsPath[1]:
        return lsPath[0];
    lsPath = os.path.split(lsPath[0]);
    return lsPath[0];

#for python3
def cmp(a,b):
    return ((a>b)-(a<b))

#获取目录下的所有类型文件
def getAllExtFile(pth,fromatx = ".erl"):
    jsondir = pth
    jsonfilelist = []
    for root, _dirs, files in os.walk(jsondir):
        for filex in files:          
            #print filex
            name,text = os.path.splitext(filex)
            if cmp(text,fromatx) == 0:
                jsonArr = []
                rootdir = pth
                dirx = root[len(rootdir):]
                pathName = dirx +os.sep + filex
                jsonArr.append(pathName)
                (newPath,_name) = os.path.split(pathName)
                jsonArr.append(newPath)
                jsonArr.append(name)
                jsonfilelist.append(jsonArr)
            elif fromatx == ".*" :
                jsonArr = []
                rootdir = pth
                dirx = root[len(rootdir):]
                pathName = dirx +os.sep + filex
                jsonArr.append(pathName)
                (newPath,_name) = os.path.split(pathName)
                jsonArr.append(newPath)
                jsonArr.append(name)
                jsonfilelist.append(jsonArr)
    return jsonfilelist


#获取一个目录下的所有子目录路径
def getAllDirs(spth):
    files = getAllExtFile(spth,'.*')
    makedirstmp = []
    isOK = True
    # 分析所有要创建的目录
    for d in files:
        if d[1] != '/' and (not d[1] in makedirstmp): #创建未创建的目录层级
            tmpdir = d[1][1:]
            tmpleves = tmpdir.split('/')
            alldirs = getAllLevelDirs(tmpleves)
            for dtmp in alldirs:
                if not dtmp in makedirstmp:
                    makedirstmp.append(dtmp)
    return makedirstmp
#获取目录下的所有文件路径
def getAllFiles(spth,fromatx = '.*'):
    files = getAllExtFile(spth,fromatx)
    makedirstmp = []
    isOK = True
    # 分析所有要创建的目录
    for d in files:
        makedirstmp.append(d[0])
    return makedirstmp


def isFile(filename):
    try:
        with open(filename) as f:
            return True
    except IOError:
        return False

def finddir(arg,dirname,filenames):
    name,text = os.path.split(dirname)
    dirnametmp = str(dirname)
    if text and text[0] == '.':
        print(dirname)
        print(filenames)
        os.system('rm -r %s'%(dirname))
        return
    elif filenames:
        for f in filenames:
            if f[0] == '.' and isFile(dirname + f):
                fpthtmp = dirname + f
                if f.find(' '):
                    nf = f.replace(' ','\ ')
                    fpthtmp = dirname + nf
                print(dirname + f)
                os.system('rm  %s'%(fpthtmp))

#删除所有pth目录下的所有"."开头的文件名和目录名
def removeProjectAllHideDir(pth):
    alldirs = getAllDirs(pth)
    if not ('/' in alldirs):
        alldirs.append('/')
    for d in alldirs:
        tmpth = pth + d
        os.path.walk(tmpth, finddir, 0)


#获取一个路径中所包含的所有目录及子目录
def getAllLevelDirs(dirpths):
    dirleves = []
    dirtmp = ''
    for d in dirpths:
        dirtmp += '/' + d
        dirleves.append(dirtmp)
    return dirleves

#在outpth目录下创建ndir路径中的所有目录，是否使用决对路径
def makeDir(outpth,ndir):
    tmpdir = ''
    if ndir[0] == '/':
        tmpdir = outpth + ndir
    else:
        tmpdir = outpth + '/' + ndir
    print(tmpdir)
    if not os.path.exists(tmpdir):
        os.mkdir(tmpdir)

# 创建一个目录下的所有子目录到另一个目录
def createDirs(spth,tpth):
    files = getAllExtFile(spth,'.*')
    makedirstmp = []
    isOK = True
    # 分析所有要创建的目录
    tmpfpth = fpth
    for d in files:
        if d[1] != '/' and (not d[1] in makedirstmp): #创建未创建的目录层级
            tmpdir = d[1][1:]
            tmpleves = tmpdir.split('/')
            alldirs = getAllLevelDirs(tmpleves)
            for dtmp in alldirs:
                if not dtmp in makedirstmp:
                    makeDir(tpth,dtmp)
                    makedirstmp.append(dtmp)

# 替换文件名
def replaceFileName(path,sname,replaceStr,tostr):
    a = sname
    tmpname = a.replace(replaceStr, tostr)
    outpath = path + tmpname
    oldpath = path + sname
    cmd = "mv %s %s"%(oldpath,outpath)
    print(cmd)
    os.system("mv %s %s"%(oldpath,outpath))

# 替换目录下的文件名中某个字符串为其他字符串
def renameDir(sdir,replacestr,tostr,exittype):
    files = getAllExtFile(sdir,fromatx = exittype)
    allfilepath = []
    for f in files:
        tmppath = sdir + f[1]
        filename = f[2] + exittype
        allfilepath.append([tmppath,filename])
    for p in allfilepath:
        replaceFileName(p[0], p[1], replacestr, tostr)


def getFileNameFromPath(fpth):
    tmp = fname.split('/')[-1]
    fname = tmp.split('.')[0]
    return fname

def rmfileWithExp(fpths,exps):
    for fp in fpths:
        for exp in exps:
            explen = len(exp)
            if fp[-explen:] == exp:
                rmcmd = '/bin/rm %s'%(fp)
                print(rmcmd)
                os.system(rmcmd)

def isHeaveMakeFile(pth):
    if os.path.exists(pth + '/Makefile'):
        return pth + '/Makefile'
    elif os.path.exists(pth + '/makefile'):
        return pth + '/makefile'
    elif os.path.exists(pth + '/MakeFile'):
        return pth + '/MakeFile'
    else:
        return None

def getMkPthWithServerBase(mkfpth):
    basepth = '/home/mage/Desktop/servercode/src/ServerEngine/Zone/Src'
    pthtmp = mkfpth[len(basepth)+1:]
    return pthtmp

def changepthInMKfile(mkfpth,lines):

    pthtmp = getMkPthWithServerBase(mkfpth)
    print pthtmp
    dirs = pthtmp.split('/')
    basesrcpth = (len(dirs)-1)*'../' + 3*'../'          #servercode/src/
    zonepth = (len(dirs)-1)*'../' + '../'               #servercode/src/ServerEngine/Zone/
    serverEnginepth = (len(dirs)-1)*'../' + 2*'../'     #servercode/src/ServerEngine/
    servercodepth = serverEnginepth + '../../'          #servercode/
    taflibpth = servercodepth + 'tool/taf/taf/'        #servercode/tool/taf/taf/

    nlines = []

    for n in range(len(lines)):
        l = lines[n]
        if l[0] != '#' and (l.find('/home/mage') != -1 or l.find('/home/tafjce') != -1):  #include
            l = ' '.join(l.split())
        if l.find('INCLUDE +=-I/home/mage/tafjce/Common/uuid') != -1 and l[0] != '#':
            l = 'INCLUDE +=-I' + basesrcpth + 'Common/uuid\n'
        if l.find('INCLUDE += -I/home/mage/tafjce/Common/uuid') != -1 and l[0] != '#':
            l = 'INCLUDE +=-I' + basesrcpth + 'Common/uuid\n'
        elif l.find('include /home/tafjce/ServerEngine/DALComm/DALComm.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'DALComm/DALComm.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/CommInclude.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'CommInclude.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/CommLib.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'CommLib.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/DbAccess/DbAccess.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'DbAccess/DbAccess.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/NameServer/NameServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'NameServer/NameServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/RoleServer/RoleServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'RoleServer/RoleServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/RouterServer/RouterServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'RouterServer/RouterServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/FightDataServer/FightDataServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'FightDataServer/FightDataServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/LegionServer/LegionServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'LegionServer/LegionServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/ConvertCodeServer/ConvertCodeServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'ConvertCodeServer/ConvertCodeServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/DbAccess/DbAccess.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'DbAccess/DbAccess.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/PayReturnServer/PayReturnServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'PayReturnServer/PayReturnServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/SnapshotServer/SnapshotServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'SnapshotServer/SnapshotServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/LJSDKServer/LJSDKServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'LJSDKServer/LJSDKServer.mk\n'
        elif l.find('include /home/tafjce/ServerEngine/QQYYBPayServer/QQYYBPayServer.mk') != -1 and l[0] != '#':
            l = 'include ' + serverEnginepth + 'QQYYBPayServer/QQYYBPayServer.mk\n'
        elif l.find('include /home/mage/Documents/tool/taf/makefile.taf') != -1 and l[0] != '#':
            l = 'include ' + taflibpth + 'makefile.taf\n'
        nlines.append(l)

    outstr = ''
    for l in nlines:
        outstr += l
    return outstr

def changeMakeFIle(mkfpth):
    f = open(mkfpth,'r')
    lines = f.readlines()
    f.close()

    newfiletxt = changepthInMKfile(mkfpth,lines)

    f = open(mkfpth + '_newback','w')
    f.write(newfiletxt)
    f.close()



def changeMakeFilePth(dirpth):
    ds = getAllDirs(dirpth)
    mkpths = []
    for p in ds:
        mkpth = isHeaveMakeFile(dirpth  + p)
        if mkpth:
            mkpths.append(mkpth)

    for f in mkpths:
        # print(f)
        changeMakeFIle(f)
        # break




def main(pconf):
    # pths = getAllExtFile('.','.*')

    # fs = []

    # for f in pths:
    #     tmp = '.' + f[0]
    #     fs.append(tmp)
    
    # if len(pconf) > 1:
    #     rmfileWithExp(fs,pconf[1:])
    # else:
    #     print('need set rm file exp')
    changeMakeFilePth(cur_file_dir())


#测试
if __name__ == '__main__':
    main(sys.argv)
    
