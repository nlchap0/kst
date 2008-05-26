/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2008 The University of Toronto                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "sampleplugin.h"
#include "objectstore.h"
#include "ui_samplepluginconfig.h"

static const QString& VECTOR_IN = "Vector In";
static const QString& SCALAR_IN = "Scalar In";
static const QString& STRING_IN = "String In";
static const QString& VECTOR_OUT = "Vector Out";
static const QString& SCALAR_OUT = "Scalar Out";
static const QString& STRING_OUT = "String Out";


class ConfigWidgetSamplePluginInternal : public QWidget, public Ui_SamplePluginConfig {
  public:
    ConfigWidgetSamplePluginInternal(QWidget *parent) : QWidget(parent), Ui_SamplePluginConfig() { 
      setupUi(this); 
    }
};


class ConfigWidgetSamplePlugin : public QWidget {
  public:
    ConfigWidgetSamplePlugin() : QWidget(0L) {
      QGridLayout *layout = new QGridLayout(this);
      _widget = new ConfigWidgetSamplePluginInternal(this);
      layout->addWidget(_widget, 0, 0);
      layout->activate();
    }

    ~ConfigWidgetSamplePlugin() {}

    ConfigWidgetSamplePluginInternal *_widget;
};


SamplePluginSource::SamplePluginSource(Kst::ObjectStore *store, const Kst::ObjectTag& tag)
: Kst::BasicPlugin(store, tag) {
}


SamplePluginSource::~SamplePluginSource() {
}


QString SamplePluginSource::_automaticDescriptiveName() const {
  return QString("Test Plugin Object");
}


bool SamplePluginSource::algorithm() {
   //Do nothing
  return true;
}


QStringList SamplePluginSource::inputVectorList() const {
  return QStringList( VECTOR_IN );
}


QStringList SamplePluginSource::inputScalarList() const {
  return QStringList( SCALAR_IN );
}


QStringList SamplePluginSource::inputStringList() const {
  return QStringList( STRING_IN );
}


QStringList SamplePluginSource::outputVectorList() const {
  return QStringList( VECTOR_OUT );
}


QStringList SamplePluginSource::outputScalarList() const {
  return QStringList( SCALAR_OUT );
}


QStringList SamplePluginSource::outputStringList() const {
  return QStringList( STRING_OUT );
}


QString SamplePlugin::pluginName() const { return "Sample DataObject Plugin"; }

Kst::DataObject *SamplePlugin::create(Kst::ObjectStore *store,
                               Kst::ObjectTag &tag, Kst::VectorPtr vector) const {

  SamplePluginSource* object = store->createObject<SamplePluginSource>(tag);

  object->setInputVector(VECTOR_IN, vector);
  object->setPluginName(pluginName());

  object->writeLock();
  object->update();
  object->unlock();

  return object;

  return new SamplePluginSource(store, tag);
}

QWidget *SamplePlugin::configWidget(Kst::ObjectPtr objectPtr, Kst::VectorPtr vector) const {
  Q_UNUSED(objectPtr);
  ConfigWidgetSamplePlugin *config = new ConfigWidgetSamplePlugin();
  return config;
}

Q_EXPORT_PLUGIN2(kstplugin_sampleplugin, SamplePlugin)

// vim: ts=2 sw=2 et
