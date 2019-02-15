<html>
	<head>
		<style>
		<title>右键菜单Demo</title>
		.widget{display:inline-block;background:#ff9900;}
		.box{width:50px;height:50px;background:#00b7ee;margin:5px;float:left;}
        
		.rk_menubox{width:100px;border:1px solid #ddd;position:absolute;z-index:999;background:#fff;}
		.rk_menuitem{line-height:20px;cursor:pointer;padding:0px 5px;}
		.rk_menuitem:hover{background:#f4f4f4;}

        </style> 
		<script type="text/javascript" src="js/jquery-1.4.2.min.js"></script>
		<script type="text/javascript" src="js/jquery.min.js"></script>
		<script type="text/javascript">
	$(function(){
    var html='';
    html +='<div id="qj_box" class="widget" >';
    for(var i=0;i<10;i++){
      html += '<div id="box'+i+'" class="box" >'+i+'</div>';
    }
    html +='</div>';
    
    if($('#qj_box')[0] ==null ){
      $('body').append(html);
    }
    
    // 判断鼠标点击是由那个键触发的，1是左键，2是滚轮键，3是右键
    $('.box').mousedown(function(event){       
      if(event.which==3){
        var itemId=$(this).attr('id');
        showMenu(itemId);
      }else{
        closeMenu();
      }
    });
    
    // 左键点击关闭自定义菜单
    $(document).on('click',function(){
      closeMenu();
    });
  });
  
  // 屏蔽浏览器自带的右键
  document.oncontextmenu=function(event){
    if($(event.target).attr('class')=='rk_menubox'){
      return false;
    }
  };
  
  // 弹出菜单代码
  function showMenu(itemId){     
    var mhtml='<div id="rk_menubox" class="rk_menubox">' +
        '<div class="rk_menuitem" onclick="closeItem('+itemId+',1)">关闭此标签</div> ' +
        '<div class="rk_menuitem" onclick="closeItem('+itemId+',2)">关闭其他标签</div> ' +
        '<div class="rk_menuitem" onclick="closeItem('+itemId+',3)">关闭所有标签</div>'+
        '</div>';
    
    if($('#rk_menubox')[0]==null){
      $('body').append(mhtml);
    }
 
    var evt=window.event || arguments[0];
    
    // 获取鼠标右键按下后的位置,据此定义菜单显示的位置
    var rightedge=$('#rk_menubox').width()+evt.clientX;
    
    // 判断弹出的菜单是否有溢出浏览器窗口的宽度
    if(rightedge>$(window).width()){
      var _left=evt.clientX-$('#rk_menubox').width();      
      $('#rk_menubox').css({top:evt.clientY+'px',left:_left+'px'});
    }else{
      $('#rk_menubox').css({top:evt.clientY+'px',left:evt.clientX+'px'});
    }    
  }
  
  function closeMenu(){
    if($('#rk_menubox')[0]!=null){
      $('#rk_menubox').remove();
    }
  }
  
  function closeItem(tag,opt){
    var tagid=$(tag).attr('id');
    if(opt==1){
      $('#qj_box').children().filter('div[id='+tagid+']').remove();
    }else if(opt==2){
      $('#qj_box').children().not('div[id='+tagid+']').remove();
    }else if(opt==3){
      $('#qj_box').children().remove();
    }
  }
 
</script> 
		
	</head>
	<body>
		<div id=send1 style='overflow:hidden;'>
		<q class='divMyHead'></q><q id=send1text class='triangle-right right'>2223</q>
		</div>

	</body>
	
<html>