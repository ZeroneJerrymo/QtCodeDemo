$(function () {
	$("p").contextMenu({
		width: 80, // width
		itemHeight: 30, // 菜单项height
		bgColor: "#ffffff", // 背景颜色
		color: "#000000", // 字体颜色
		fontSize: 12, // 字体大小
		hoverColor: "#000000", // hover字体颜色
		//hoverBgColor: "#99CC66", // hover背景颜色
		hoverBgColor: "#d2d2d2", // hover背景颜色
		target: function(ele) { // 当前元素--jq对象
			console.log(ele);
		},
		menu: [{ // 菜单项
				text: "新增",
				icon: "img/11.png",
				callback: function() {
					alert("新增"+trIndex);
				}
			}, {
				text: "复制",
				icon: "img/22.png",
				callback: function() {
					alert("复制"+trIndex);
				}
			}, {
				text: "粘贴",
				icon: "img/33.png",
				callback: function() {
					alert("粘贴"+trIndex);
				}
			}, {
				text: "删除",
				icon: "img/44.png",
				callback: function() {
					alert("删除"+trIndex);
				}
			}
		]
	});	
});