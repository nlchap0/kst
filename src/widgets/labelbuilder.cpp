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

#include "labelbuilder.h"

#include "objectstore.h"

namespace Kst {

LabelBuilder::LabelBuilder(QWidget *parent, ObjectStore *store)
  : QWidget(parent), _store(store) {

  setupUi(this);

  connect(_label, SIGNAL(textChanged(const QString &)), this, SIGNAL(labelChanged(const QString &)));
  connect(_strings, SIGNAL(selectionChanged(QString)), this, SLOT(labelUpdate(const QString&)));
  connect(_scalars, SIGNAL(selectionChanged(QString)), this, SLOT(labelUpdate(const QString&)));
}


LabelBuilder::~LabelBuilder() {
}


void LabelBuilder::setObjectStore(ObjectStore *store) {
  _store = store;
  _scalars->setObjectStore(store);
  _strings->setObjectStore(store);
}


QString LabelBuilder::labelText() const {
  return _label->text();
}


void LabelBuilder::setLabelText(const QString &label) {
  _label->setText(label);
}


void LabelBuilder::labelUpdate(const QString& string) {
  QString label = _label->text();
  label += "[" + string + "]";
  _label->setText(label); 
}

}

// vim: ts=2 sw=2 et