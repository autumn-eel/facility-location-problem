canvas=document.getElementById("canvas");
ctx=canvas.getContext("2d");

inputFile=document.getElementById("file");
outputFile=document.getElementById("file2");

n=0,m=0;
points=[];
f=[];
flag=[];
x=[];
ans=[];
events=[];
C=[];
used=[];

function f1(text){
	data=text.split(/\r\n|\r|\n/);
	nm=data[0].split(' ');
	n=Number(nm[0]);m=Number(nm[1]);
	cnt=1;
	for(i=0;i<n+m;i++){
		p=data[cnt].split(' ');
		if(points.length<=i)points.push([]);
		points[i]=[Number(p[0]),Number(p[1])];
		cnt++;
	}
	for(i=0;i<m;i++){
		f[i]=Number(data[cnt]);
		cnt++;
	}
}
function f2(text){
	data=text.split(/\r\n|\r|\n/);
	cnt=0;
	for(i=0;i<m;i++)flag[i]=0;
	for(i=0;i<n;i++)used[i]=0;
	while(1){
		line=data[cnt];
		cnt++;
		ele=line.split(' ');
		if(ele[0]=="end")break;
		for(i=0;i<ele.length;i++)ele[i]=Number(ele[i]);
		events.push(ele);
	}
	for(i=0;i<m;i++){
		x[i]=Number(data[cnt]);
		cnt++;
	}
	for(i=0;i<n;i++){
		ans[i]=Number(data[cnt]);
		cnt++;
	}
	c=0;
	id=setInterval(function(){
		if(c==events.length){
			id2=setInterval(function(){
				render(events.length);
				clearInterval(id2);
			},1000);
			clearInterval(id);
		}
		else{
			render(c);
			c++;
		}
	},5);
}

function fileChange(ev){
	target=ev.target;
	files=target.files;
	reader=new FileReader();
	text=reader.readAsText(files[0]);
	reader.onload=function(ev){
		f1(reader.result);
	}
}
function fileChange2(ev){
	target=ev.target;
	files=target.files;
	reader=new FileReader();
	text=reader.readAsText(files[0]);
	reader.onload=function(ev){
		f2(reader.result);
	}
}
inputFile.addEventListener("change",fileChange,false);
outputFile.addEventListener("change",fileChange2,false);

function sample(){
	req=new XMLHttpRequest();
	req.open("GET","in.txt",true);
	req.onload=function(){
		f1(req.responseText);
	};
	req.send();
	req2=new XMLHttpRequest();
	req2.open("GET","out.txt",true);
	req2.onload=function(){
		f2(req2.responseText);
	};
	req2.send();
}

function render(tim){
	ctx.clearRect(0,0,canvas.width,canvas.height);
	if(tim<events.length){
		for(i=0;i<=tim;i++){
			ele=events[i];
			if(ele.length==1){
				flag[ele[0]]=1;
			}
			else if(ele[0]==-1){
				used[ele[1]]=true;
			}
			else{
				ctx.beginPath();
				ctx.strokeStyle="blue";
				ctx.moveTo(points[ele[0]][0],points[ele[0]][1]);
				ctx.lineTo(points[ele[1]+n][0],points[ele[1]+n][1]);
				ctx.stroke();
			}
		}
	}
	else{
		for(i=0;i<m;i++)C[i]=0;
		ctx.strokeStyle="blue";
		for(i=0;i<n;i++){
			ctx.beginPath();
			ctx.moveTo(points[i][0],points[i][1]);
			ctx.lineTo(points[ans[i]+n][0],points[ans[i]+n][1]);
			ctx.stroke();
			C[ans[i]]++;
		}
	}
	ctx.strokeStyle="black";
	ctx.fillStyle="white";
	for(i=0;i<n+m;i++){
		ctx.beginPath();
		ctx.arc(points[i][0],points[i][1],(i>=n?9:3),0,Math.PI*2);
		if(i>=n){
			blue=0;
			green=0;
			green=255-f[i-n]*255/500;
			ctx.fillStyle="rgb(0,"+green+","+blue+")";
			if((tim<events.length&&flag[i-n])||(tim==events.length&&C[i-n])){
				ctx.strokeStyle="red";
				ctx.lineWidth=4;
			}
		}
		else{
			if(used[i])ctx.fillStyle="black"
		}
		ctx.fill();
		ctx.stroke();
		ctx.lineWidth=1;
		ctx.strokeStyle="black";
		ctx.fillStyle="white";
	}
}
