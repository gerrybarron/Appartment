
(function($){
  $(function(){
    //$('.button-collapse').sideNav();
    $('.parallax').parallax();
    $('.carousel').carousel();
     $('.slider').slider({full_width: true});
     $('.collapsible').collapsible({
      accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
    });
     $('.tooltipped').tooltip({delay: 50});
     $('.modal').modal();
      $('.datepicker').pickadate({
    selectMonths: true, // Creates a dropdown to control month
    selectYears: 15 // Creates a dropdown of 15 years to control year
    });
      $('select').material_select();
  }); 
  // end of document ready
})(jQuery); // end of jQuery name space
/* -----------------------------------------------
/* Author : Vincent Garreau  - vincentgarreau.com
/* MIT license: http://opensource.org/licenses/MIT
/* Demo / Generator : vincentgarreau.com/particles.js
/* GitHub : github.com/VincentGarreau/particles.js
/* How to use? : Check the GitHub README
/* v2.0.0
/* ----------------------------------------------- */

