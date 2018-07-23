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

		Console.println("Job done...");
		return;
	}
}