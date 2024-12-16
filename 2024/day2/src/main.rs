use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn parse_input(seq: &Vec<&str>) -> Vec<u32> {
    let mut result: Vec<u32> = Vec::new();
    for s in seq {
        result.push(s.parse().unwrap());
    }

    return result;
}

fn remove_element(seq: &Vec<u32>, index: usize) -> Vec<u32> {
    let mut result: Vec<u32> = Vec::new();
    for i in 0..seq.len() {
        if i != index {
            result.push(seq[i]);
        }
    }

    return result;
}

fn is_report_safe(seq: &Vec<u32>) -> bool {
    if seq.len() < 2 {
        return true;
    }

    let inc = seq[0] < seq[1];
    let mut i = 0;
    while i < seq.len() - 1 {
        if inc != (seq[i] < seq[i + 1]) {
            return false;
        }

        let diff = seq[i].abs_diff(seq[i + 1]);
        if diff < 1 || diff > 3 {
            return false;
        }

        i += 1;
    }

    return true;
}

fn is_report_safe2(seq: &Vec<u32>) -> bool {
    if seq.len() < 3 {
        return true;
    }

    let inc = seq[0] < seq[1];
    let mut prev = seq[0];
    let mut i = 1;
    let mut missed = false;
    while i < seq.len() {
        if inc != (prev < seq[i]) {
            if !missed {
                missed = true;
                i += 1;
                continue;
            }
            else {
                return false;
            }
        }

        let diff = prev.abs_diff(seq[i]);
        if diff < 1 || diff > 3 {
            if !missed {
                missed = true;
                i += 1;
                continue;
            }
            else {
                return false;
            }
        }

        prev = seq[i];
        i += 1;
    }

    return true;
}

fn is_report_safe3(seq: &Vec<u32>) -> bool {
    if !is_report_safe2(seq) {
        return is_report_safe(&seq[1..].to_vec());
    }

    return true;
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // Grab the input from the file
    let path = Path::new("src\\input.txt");
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);

    let mut result = 0;
    let mut result2 = 0;
    for line in reader.lines() {
        let line = line?;
        let seq: Vec<&str> = line.split(" ").collect();
        let parsed_input = parse_input(&seq);
        
        if is_report_safe(&parsed_input) {
            result += 1;
            result2 += 1;
        }
        else {
            for i in 0..parsed_input.len() {
                let removed = remove_element(&parsed_input, i);
                if is_report_safe(&removed) {
                    result2 += 1;
                    if !is_report_safe3(&parsed_input) {
                        println!("{:?}", parsed_input);
                    }
                    break;
                }
            }
        }
    }

    println!("Safe reports: {result}");
    println!("Safe reports 2: {result2}");
    Ok(())
}
