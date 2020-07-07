use crate::filehandler::FileHandler::FileHandler;

#[allow(non_snake_case)]
pub fn DataSerialization(inputFile:String, serializationType:i32, outFile:String, numberOfTweets:i64, round:i32, taskset:bool){

    let log_file_name = format!("{}{}{}{}{}", "bin/benchmark/writeobjects/result_java_writeobjects_", numberOfTweets, "_", round, ".txt");

    let file_handler = FileHandler::new(outFile, serializationType);
}