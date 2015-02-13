(function($){
$(document).ready(function(){
  var resizeDivs = function(divClass){
    var maxHeight = 0;  
    var divWrapper = $(divClass);
    divWrapper.each(function(e){
      var height = $(this).height();
      if(maxHeight < height)
        maxHeight = height;
    });
    divWrapper.each(function(e){
      $(this).css('height', maxHeight);
    }); 
  };
  $('.show-modules-row-checkbox').each(function(){
    var r_id = $(this).attr('id').split('_').slice(-1)[0] ;
    $(this).bind('click',function(e){
      $('.modules-row-'+r_id).toggle('fast');
      resizeDivs('.pub-server-modules-data-content-div-wrapper-'+r_id);
    });
  })
  $('.show-tabular-data-row-checkbox').each(function(){
    var r_id = $(this).attr('id').split('_').slice(-1)[0];
    $(this).bind('click',function(e){
      $('.tabular-data-row-'+r_id).toggle('fast');
      resizeDivs('.pub-server-tabular-data-content-div-wrapper-'+r_id);
    });
  })
});
})(jQuery);
