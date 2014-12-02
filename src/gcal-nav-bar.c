/* -*- mode: c; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/*
 * gcal-nav-bar.c
 *
 * Copyright (C) 2012 - Erick Pérez Castellanos
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "gcal-nav-bar.h"
#include "gcal-utils.h"

#include <glib/gi18n.h>

typedef struct
{
  GtkWidget *back_button;
  GtkWidget *forward_button;

  GtkWidget *left_label;
  GtkWidget *right_label;
} GcalNavBarPrivate;

enum
{
  PROP_0,
  PROP_LEFT_HEADER,
  PROP_RIGHT_HEADER
};

static void           gcal_nav_bar_set_property          (GObject        *object,
                                                          guint           property_id,
                                                          const GValue   *value,
                                                          GParamSpec     *pspec);

static void           gcal_nav_bar_get_property          (GObject        *object,
                                                          guint           property_id,
                                                          GValue         *value,
                                                          GParamSpec     *pspec);

G_DEFINE_TYPE_WITH_PRIVATE (GcalNavBar, gcal_nav_bar, GTK_TYPE_GRID)

static void
gcal_nav_bar_class_init (GcalNavBarClass *klass)
{
  GtkWidgetClass *widget_class;
  GObjectClass *object_class;

  object_class = G_OBJECT_CLASS (klass);
  object_class->set_property = gcal_nav_bar_set_property;
  object_class->get_property = gcal_nav_bar_get_property;

  g_object_class_install_property (
      object_class,
      PROP_LEFT_HEADER,
      g_param_spec_string ("left-header",
                           "Left Header",
                           "The text of the left header",
                           "",
                           G_PARAM_CONSTRUCT |
                           G_PARAM_READWRITE));

  g_object_class_install_property (
      object_class,
      PROP_RIGHT_HEADER,
      g_param_spec_string ("right-header",
                           "Right Header",
                           "The text of the right header",
                           "",
                           G_PARAM_CONSTRUCT |
                           G_PARAM_READWRITE));

  widget_class = GTK_WIDGET_CLASS (klass);

  /* Setup the template GtkBuilder xml for this class */
  gtk_widget_class_set_template_from_resource (widget_class, "/org/gnome/calendar/nav_bar.ui");

  /* Bind internals widgets */
  gtk_widget_class_bind_template_child_private (widget_class, GcalNavBar, left_label);
  gtk_widget_class_bind_template_child_private (widget_class, GcalNavBar, right_label);
}



static void
gcal_nav_bar_init (GcalNavBar *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
}

static void
gcal_nav_bar_set_property (GObject       *object,
                           guint          property_id,
                           const GValue  *value,
                           GParamSpec    *pspec)
{
  GcalNavBarPrivate *priv;
  priv = gcal_nav_bar_get_instance_private (GCAL_NAV_BAR (object));

  switch (property_id)
    {
    case PROP_LEFT_HEADER:
      gtk_label_set_text (GTK_LABEL (priv->left_label),
                          g_value_get_string (value));
      break;
    case PROP_RIGHT_HEADER:
      gtk_label_set_text (GTK_LABEL (priv->right_label),
                          g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
gcal_nav_bar_get_property (GObject       *object,
                              guint          property_id,
                              GValue        *value,
                              GParamSpec    *pspec)
{
  GcalNavBarPrivate *priv;
  priv = gcal_nav_bar_get_instance_private (GCAL_NAV_BAR (object));

  switch (property_id)
    {
    case PROP_LEFT_HEADER:
      g_value_set_string (value,
                          gtk_label_get_text (GTK_LABEL (priv->left_label)));
      break;
    case PROP_RIGHT_HEADER:
      g_value_set_string (value,
                          gtk_label_get_text (GTK_LABEL (priv->right_label)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

/* Public API */
/**
 * gcal_nav_bar_new:
 *
 * Since: 0.1
 * Return value: A new #GcalNavBar
 * Returns: (transfer full):
 **/
GtkWidget*
gcal_nav_bar_new (void)
{
  return g_object_new (GCAL_TYPE_NAV_BAR, NULL);
}
