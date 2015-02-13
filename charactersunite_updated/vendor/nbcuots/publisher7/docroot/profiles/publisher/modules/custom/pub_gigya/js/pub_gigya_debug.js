(function($) {

Drupal = Drupal || {};
Drupal.GigyaAdmin = Drupal.GigyaAdmin || {};

var gigya_user = null;

/**
 * Function : dump()
 * Arguments: The data - array,hash(associative array),object
 *  The level - OPTIONAL
 * Returns  : The textual representation of the array.
 *  This function was inspired by the print_r function of PHP.
 * This will accept some data as the argument and return a
 * text that will be a more readable version of the
 * array/hash/object that is given.
 */
Drupal.GigyaAdmin.dump = function(arr,level){
  var dumped_text = "";
  if(!level) level = 0;
  //The padding given at the beginning of the line.
  var level_padding = "";
  for(var j=0;j<level+1;j++) level_padding += "    ";
  if(typeof(arr) == 'object') { //Array/Hashes/Objects
    for(var item in arr) {
      var value = arr[item];
      if(typeof(value) == 'object') { //If it is an array,
        dumped_text += level_padding + "'" + item + "' ...\n";
        dumped_text += Drupal.GigyaAdmin.dump(value,level+1);
      } else {
        dumped_text += level_padding + "'" + item + "' => \"" + value + "\"\n";
      }
    }
  } else { //Stings/Chars/Numbers etc.
   dumped_text = "===>"+arr+"<===("+typeof(arr)+")";
  }
  return dumped_text;
}

Drupal.GigyaAdmin.print = function(o){
  var str='';
  for(var p in o){
    if(typeof o[p] == 'string'){
      str+= p + ': ' + o[p]+'; </br>';
    }else{
      str+= p + ': { </br>' + Drupal.GigyaAdmin.print(o[p]) + '}';
    }
  }
  return str;
}

Drupal.GigyaAdmin.notifyRegistration = function(){
  $.ajax({
    url: '/admin/config/services/gigya/debug?' + Drupal.settings.gigya.apiKey,
    type: 'POST',
    data: { method: 'notifyRegistration', uid: gigya_user.UID, deliver_ajax: true },
    success: function(response) {
      $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(response)+'</pre>');
      Drupal.GigyaAdmin.grabUserInfo();
    }
  });
}

Drupal.GigyaAdmin.deleteAccount = function(){
  $.ajax({
    url: '/admin/config/services/gigya/debug?' + Drupal.settings.gigya.apiKey,
    type: 'POST',
    data: { method: 'deleteAccount', uid: gigya_user.UID, deliver_ajax: true },
    success: function(response) {
      $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(response)+'</pre>');
      Drupal.GigyaAdmin.grabUserInfo();
    }
  });
}

Drupal.GigyaAdmin.grabUserInfo = function(){
  gigya.services.socialize.getUserInfo({ callback: function(o) {
    gigya_user = o.user;
    $('#userinfo').html('<pre class="prettyprint lang-js">'+Drupal.GigyaAdmin.dump(o)+'</pre>');
  }});
}

Drupal.behaviors.GigyaAdmin = {
  attach: function(context) {
    $('#login-fb').click(function() {
      gigya.socialize.login({
        provider: 'facebook',
        callback: function(o) {
          gigya_user = o.user;
          $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(o)+'</pre>');
        }
      })
    });

    $('#login-tw').click(function() {
      gigya.socialize.login({
        provider: 'twitter',
        callback: function(o) {
          gigya_user = o.user;
          $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(o)+'</pre>');
        }
      })
    });

    $('#logout').click(function() {
      gigya.socialize.logout({ callback: function(o) {
        $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(o)+'</pre>');
      }});
    });

    $('#remove').click(function() {
      gigya.socialize.removeConnection({ callback: function(o) {
        $('#userinfo').html('<pre>'+Drupal.GigyaAdmin.dump(o)+'</pre>');
      }});
    });

    $('#logoutremove').click(function() {
      gigya.socialize.removeConnection({ callback: function(o) {
        gigya.socialize.logout({ callback: function(o) {
          Drupal.GigyaAdmin.grabUserInfo();
        }});
      }});
    });

    $('#register').click(function() {
        Drupal.GigyaAdmin.notifyRegistration();
    });

    $('#delete').click(function() {
        Drupal.GigyaAdmin.deleteAccount();
    });

    $('#refresh').click(function() {
        Drupal.GigyaAdmin.grabUserInfo();
    });

    Drupal.GigyaAdmin.grabUserInfo();
  }
};

})(jQuery);
