/*
 * @Class: App
 * @Description: Sample Class file for Mate Programming 
 * 				 Language using Class Syntax.
 * @Author: TOUBE P.Pierre 
 */
namespace test;

use mate.io.Console;
use mate.lang.io.*;
use mate.Json;

class App {
	
	App(){

	}
	public static Void main(Array args){
		Object jsonData = Json.parseFile("source.json");
		Array datas = jsonData.datas;
		String outputDir = "out/model/";
		Object parseRepport;

		foreach(Object item in datas){
			File out = File(outputDir+item.name+".txt");
			Family f = Family(item);
			parseRepport = f.parse(out);
		}empty{
			Console.println("No data to process");
		}

		if(i>=10){
			Console.println("i is greater than 10");
		}else if(i>=0){
			Console.println("i is lower than 10 but greater than 0");
		}else{
			Console.println("i is lower 0");
		}

		switch(i){
			case 1:
				1+2;
				1+2;
				1+2;
				break(1);
			case 2:
				1+2;
				break(2);
				1+2;
			default:
				1+2;
				1+2;
				break;
		}

		Console.println("Job done...");
		return;
	}
}