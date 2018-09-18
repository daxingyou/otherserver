var querystring = require('querystring');
var util = require('util');
var crypto = require('crypto');

var redis = require('redis'),
    port = 6379,
    host = '127.0.0.1',
    opts = {},
    client = redis.createClient(port, host, opts);

client.on('connect',function(){
    console.log('connect');
});

client.on('ready', function(err){
    console.log('ready');
    
    });

function insertData() {
    var rf=require("fs");
    var data=rf.readFileSync("aa.json","utf-8");
    postData = JSON.parse(data);
    
    var i = 0;
    for(key in postData[0]){
		console.log("Key:"+key+"\tVaule:"+postData[0][key]);
        client.set(key, postData[0][key], redis.print);
	}    
    return true;
}

insertData();