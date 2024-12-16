use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use regex::Regex;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // Grab the input from the file
    let path = Path::new("src\\input.txt");
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);

    // Define the regex pattern
    let re = Regex::new(r"mul\(\d{1,3},\d{1,3}\)")?;

    let mut result = 0;
    let mut result2 = 0;
    let mut enabled = "".to_string();
    let mut dont = false;
    for line in reader.lines() {
        let line = line?;
        let mut i;
        let mut j;
        if dont {
            i = line.find("do()").unwrap_or(line.len());
            j = line[i..].find("don't()").unwrap_or(line[i..].len()) + i;
            if line.rfind("do()").unwrap_or(0) > line.rfind("dont()").unwrap_or(0) {
                dont = false;
            }
        }
        else {
            i = 0;
            j = line.find("don't()").unwrap_or(line.len());
            if line.rfind("dont()").unwrap_or(0) > line.rfind("do()").unwrap_or(0) {
                dont = true;
            }
        }

        while i < line.len() || j < line.len() {
            enabled += &line[i..j];
            i = line[j..].find("do()").unwrap_or(line[j..].len()) + j;
            j = line[i..].find("don't()").unwrap_or(line[i..].len()) + i;
        }

        for m in re.find_iter(&line) {
            let mut nums = m.as_str().split(|c| c == '(' || c == ',' || c == ')');
            let a = nums.nth(1).unwrap().parse::<u32>().unwrap();
            let b = nums.nth(0).unwrap().parse::<u32>().unwrap();
            result += a * b;
        }
    }

    for m in re.find_iter(&enabled) {
        let mut nums = m.as_str().split(|c| c == '(' || c == ',' || c == ')');
        let a = nums.nth(1).unwrap().parse::<u32>().unwrap();
        let b = nums.nth(0).unwrap().parse::<u32>().unwrap();
        result2 += a * b;
    }

    println!("Result: {}", result);
    println!("Result2: {}", result2);

    Ok(())
}
