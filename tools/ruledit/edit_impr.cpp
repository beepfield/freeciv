/***********************************************************************
 Freeciv - Copyright (C) 1996 - A Kjeldberg, L Gregersen, P Unold
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
***********************************************************************/

#ifdef HAVE_CONFIG_H
#include <fc_config.h>
#endif

// Qt
#include <QGridLayout>
#include <QSpinBox>

// common
#include "improvement.h"

// ruledit
#include "ruledit.h"
#include "ruledit_qt.h"
#include "tab_tech.h"

#include "edit_impr.h"

/**********************************************************************//**
  Setup edit_impr object
**************************************************************************/
edit_impr::edit_impr(ruledit_gui *ui_in, struct impr_type *impr_in) : QDialog()
{
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  QGridLayout *impr_layout = new QGridLayout();
  QLabel *label;

  ui = ui_in;
  impr = impr_in;

  setWindowTitle(QString::fromUtf8(improvement_rule_name(impr)));

  label = new QLabel(QString::fromUtf8(R__("Build Cost")));
  label->setParent(this);

  bcost = new QSpinBox(this);
  bcost->setRange(0, 10000);
  connect(bcost, SIGNAL(valueChanged(int)), this, SLOT(set_bcost_value(int)));

  impr_layout->addWidget(label, 0, 0);
  impr_layout->addWidget(bcost, 0, 2);

  refresh();

  main_layout->addLayout(impr_layout);

  setLayout(main_layout);
}

/**********************************************************************//**
  User is closing dialog.
**************************************************************************/
void edit_impr::closeEvent(QCloseEvent *cevent)
{
  impr->ruledit_dlg = nullptr;
}

/**********************************************************************//**
  Refresh the information.
**************************************************************************/
void edit_impr::refresh()
{
  bcost->setValue(impr->build_cost);
}

/**********************************************************************//**
  Read build cost value from spinbox
**************************************************************************/
void edit_impr::set_bcost_value(int value)
{
  impr->build_cost = value;

  refresh();
}
