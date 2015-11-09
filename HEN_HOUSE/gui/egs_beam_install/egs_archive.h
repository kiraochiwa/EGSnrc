/***************************************************************************

                           egs_archive.h  -  description
                          -------------------------------------------
    copyright          : (C) 2003  National Research Council Canada
    author               : Iwan Kawrakow
    email                : iwan@irs.phy.nrc.ca
    
    modified for egs_install by: Ernesto Mainegra-Hing
    
  $Id: egs_archive.h,v 1.5 2009/11/06 15:25:10 mainegra Exp $
 ***************************************************************************/
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef EGS_ARCHIVE_
#define EGS_ARCHIVE_

#include <qtextedit.h>
#include <QEvent>
#include <QThread>

class PrivateArchive;
class QMutex;
class QThread;

class EGS_Archive {

public:

  EGS_Archive(QWidget* o = 0);
  EGS_Archive(QMutex *m = 0, QWidget* o = 0, const int &totS = 100);
  ~EGS_Archive();

  void addOutput(const char *, int type);
  void closeOutput(const char *);
  void addFile(const char *);
  void clearFiles();
  void setIODevice( QTextEdit*  io_dev );
  void stop();

  int  make();
  int extract(const char *archive, const char *start_dir=0) const;
  int listFiles(const char *archive) const;
  
  bool isZipFile(const char *archive) const;

private:

  PrivateArchive *p;
  QWidget* receiver;
};

// Define your custom event identifier
//const QEvent::Type MY_CUSTOM_EVENT = static_cast<QEvent::Type>(QEvent::User + 1);
const QEvent::Type CustomEventString = static_cast<QEvent::Type>(12345);
const QEvent::Type CustomEventInt    = static_cast<QEvent::Type>(12346);
const QEvent::Type CustomEventFloat  = static_cast<QEvent::Type>(12347);

// Define your custom event subclass
class EGSCustomEvent : public QEvent
{
    public:
        EGSCustomEvent(const QString strData):
            QEvent(CustomEventString),
            m_strData(strData)
        { }

        QString getStrData() const { return m_strData; }

        EGSCustomEvent(const int intData):
            QEvent(CustomEventInt),
            m_intData(intData)
        { }

        int getIntData() const { return m_intData; }

        EGSCustomEvent(const float floatData):
            QEvent(CustomEventFloat),
            m_floatData(floatData)
        { }

        float getFloatData() const { return m_floatData; }

    private:
        QString m_strData;
        int     m_intData;
        float   m_floatData;
};

class EGSThread : public QThread {

    public:
        EGSThread( const QString& archi, const QString& rdir );
        EGSThread( QWidget* o, const QString& archi, const QString& rdir );
        EGSThread();     
        virtual void run();
        void setArchive(const QString& archi, const QString& rdir ){
         archive = archi; dir = rdir;
        };
        int extract( const QString& archi, const QString& rdir );
       int    getStatus(){ return status;};
       void stop(){ m_exit = true; if ( ar ) ar->stop(); };

    private:
        EGS_Archive* ar;
        QMutex *mutex;
        QString archive;
        QString dir;
        uint status;
        bool m_exit;
        QWidget* receiver;
        
};

#endif
