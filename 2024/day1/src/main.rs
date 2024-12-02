use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() -> Result<(), Box<dyn std::error::Error>>{
    // Grab the input from the file
    let path = Path::new("src\\input.txt");
    let file = File::open(&path)?;
    let reader = io::BufReader::new(file);

    let mut list1: Vec<u32> = Vec::new();
    let mut list2: Vec<u32> = Vec::new();

    for line in reader.lines() {
        let line = line?;
        let loc_pair: Vec<_> = line.split("   ").collect();
        let loc0 = loc_pair[0];
        let loc1 = loc_pair[1];
        list1.push(loc0.parse().unwrap());
        list2.push(loc1.parse().expect(&format!("Couldn't parse value {line}")));
    }

    list1.sort();
    list2.sort();

    let mut result = 0;
    for i in 0..list1.len() {
        result += list1[i].abs_diff(list2[i]);
    }

    println!("Total distance: {result}");

    let mut sim = 0;
    let mut j = 0;
    for loc in list1 {
        let mut found = false;
        let mut k = 0;
        while list2[j] <= loc {
            if list2[j] == loc {
                if !found {
                    k = j;
                    found = true;
                }
                sim += loc;
            }
            j += 1;
        }
        if found {
            j = k;
        }
    }

    println!("Similarity: {sim}");

    Ok(())
}
