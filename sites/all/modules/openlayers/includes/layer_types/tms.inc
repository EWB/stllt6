<?php
// $Id: tms.inc,v 1.1.2.12 2010/06/25 16:23:51 tmcw Exp $

/**
 * @file
 * TMS Layer Type
 */

/**
 * OpenLayers TMS Layer Type class
 */
class openlayers_layer_type_tms extends openlayers_layer_type {

  function __construct($layer = array(), $map = array()) {
    parent::__construct($layer, $map);
    if (isset($this->data)) {
      $this->data += $this->options_init();
    }
    else {
      $this->data = $this->options_init();
    }
  }

  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'serverResolutions' => openlayers_get_resolutions('900913'),
      'maxExtent' => openlayers_get_extent('900913'),
      'projection' => array('900913'),
      'baselayer' => TRUE,
      'layer_handler' => 'tms',
      'type' => 'png',
    );
  }

  /**
   * Options form which generates layers
   */
  function options_form() {
    return array(
      'base_url' => array(
        '#type' => 'textfield',
        '#title' => t('Base URL'),
        '#default_value' => isset($this->data['base_url']) ? 
          $this->data['base_url'] : ''
      ),
      'layername' => array(
        '#type' => 'textfield',
        '#title' => t('Layer Name'),
        '#default_value' => isset($this->data['layername']) ?
          $this->data['layername'] : ''
      ),
      'type' => array(
        '#type' => 'select',
        '#title' => t('File Format'),
        '#options' => array(
          'png' => 'png',
          'jpg' => 'jpg'),
        '#default_value' => isset($this->data['type']) ?
          $this->data['type'] : 'png'
      ),
      'resolutions' => array(
        '#type' => 'select',
        '#multiple' => TRUE,
        '#options' => array_combine(
          array_map('strval', openlayers_get_resolutions('900913')),
          range(0, 18)
        ),
        '#title' => t('Zoom Level Range'),
        '#default_value' => isset($this->data['resolutions']) ?
          $this->data['resolutions'] :
          array_map('strval', openlayers_get_resolutions('900913'))
      ),
      'layer_type' => array(
        '#type' => 'hidden',
        '#value' => 'openlayers_layer_type_tms'
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    drupal_add_js(drupal_get_path('module', 'openlayers') 
      . '/includes/layer_types/js/tms.js');
    return $this->options;
  }
}
