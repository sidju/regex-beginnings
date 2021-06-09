extern crate regex;

use regex::RegexBuilder;

fn main() {
  let regex = RegexBuilder::new("^").multi_line(true).build().unwrap();
  let text = "\n";
  for i in regex.find_iter(text) {
    println!("Found match at index {}", i.start());
  }
}
