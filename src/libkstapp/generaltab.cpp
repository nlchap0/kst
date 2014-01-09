/***************************************************************************
 *                                                                         *
 *   copyright : (C) 2007 The University of Toronto                        *
 *                   netterfield@astro.utoronto.ca                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include "generaltab.h"



namespace Kst {

GeneralTab::GeneralTab(QWidget *parent)
  : DialogTab(parent) {

  setupUi(this);
  setTabTitle(tr("General"));

  connect(_useOpenGL, SIGNAL(stateChanged(int)), this, SIGNAL(modified()));
  connect(_maxUpdate, SIGNAL(valueChanged(int)), this, SIGNAL(modified()));
  connect(_transparentDrag, SIGNAL(stateChanged(int)), this, SIGNAL(modified()));
  connect(_antialiasPlots, SIGNAL(stateChanged(int)), this, SIGNAL(modified()));
}


GeneralTab::~GeneralTab() {
}

bool GeneralTab::useOpenGL() const {
#ifdef KST_NO_OPENGL
    return false;
#else
  return _useOpenGL->isChecked();
#endif
}


void GeneralTab::setUseOpenGL(const bool useOpenGL) {
#ifdef KST_NO_OPENGL
  _useOpenGL->setChecked(false);
#else
  _useOpenGL->setChecked(useOpenGL);
#endif
}

bool GeneralTab::transparentDrag() const {
  return _transparentDrag->isChecked();
}

void GeneralTab::setTransparentDrag(const bool transparent_drag) {
  _transparentDrag->setChecked(transparent_drag);
}

bool GeneralTab::antialiasPlot() const {
  return _antialiasPlots->isChecked();
}

void GeneralTab::setAntialiasPlot(bool antialias) {
  _antialiasPlots->setChecked(antialias);
}

int GeneralTab::minimumUpdatePeriod() const {
  return _maxUpdate->value();
}


void GeneralTab::setMinimumUpdatePeriod(const int period) {
  _maxUpdate->setValue(period);
}

}

// vim: ts=2 sw=2 et
