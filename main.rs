use core::panic;
use std::io;
use std::fs;

const ALPHABET: &[u8] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/".as_bytes();
const PADDING: &[u8] = "=".as_bytes();
const ASCII_CHARACTER: &[u8] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/!@#$%^&*(){}[]=-_\\|'\";:/?.,<>~` ".as_bytes();

fn is_ascii(v: u8) -> bool {
    v == 9 || v == 10 || v == 13 || (v >= 32 && v < 127)
}

fn encode_group(result: &mut Vec<u8>, val: usize) {
    let mut index = (val & 0xFC0000) >> 18;
    result.push(ALPHABET[index]);

    index = (val & 0x03F000) >> 12;
    result.push(ALPHABET[index]);

    index = (val & 0x000FC0) >> 6;
    result.push(ALPHABET[index]);

    index = val & 0x00003F;
    result.push(ALPHABET[index]);
}

fn base64_encode(input: &Vec<u8>) -> Vec<u8> {
    // group into 6 bit chunks
    // index alphabet and append result to output
    // retain leftover and move to next chunk
    let mut val: usize = 0;
    let mut bytes = 0;
    let mut result: Vec<u8> = Vec::new();
    for &v in input {
        bytes += 1;
        val <<= 8;
        val |= usize::from(v);
        if bytes > 2 {
            encode_group(&mut result, val);
            bytes = 0;
            val = 0;
        }
    }
    // pad
    let mut pad = 0;
    if bytes == 1 {
        val <<= 16;

        let mut index = (val & 0xFC0000) >> 18;
        result.push(ALPHABET[index]);
        //let mut index = (val & 0xFC0) >> 6;
        //result.push(ALPHABET[index]);

        //index = val & 0x3F;
        //result.push(ALPHABET[index]);

        index = (val & 0x03F000) >> 12;
        result.push(ALPHABET[index]);

        pad = 2;
    } else if bytes == 2 {
        val <<= 2;
        let mut index = (val & 0x03F000) >> 12;
        result.push(ALPHABET[index]);
        index = (val & 0xFC0) >> 6;
        result.push(ALPHABET[index]);
        index = val & 0x3F;
        result.push(ALPHABET[index]);
        pad = 1;
    }

    while pad > 0 {
        result.push(PADDING[0]);
        pad -= 1;
    }
    result
}

fn decode_hex(s: &String) -> Vec<u8> {
    if s.len() % 2 != 0 {
        panic!("Invalid hex string length");
    }
    let mut result: Vec<u8> = Vec::new();
    let mut iter = s.chars().peekable();
    while iter.peek().is_some() {
        let v: String = iter.by_ref().take(2).collect();
        result.push(u8::from_str_radix(v.as_str(), 16).unwrap());
    }
    result
}

fn encode_hex(v: &Vec<u8>) -> String {
    let mut result = String::new();
    v.iter().for_each(
        |b| result.push_str(format!("{:02x}", b).as_str())
    );
    result
}

fn xor(b1: &Vec<u8>, b2: &Vec<u8>) -> Vec<u8> {
    let mut result: Vec<u8> = Vec::new();
    if b1.len() != b2.len() {
        panic!("Cannot XOR buffers of unequal length")
    }
    for (i, &v) in b1.iter().enumerate() {
        result.push(v ^ b2[i])
    }
    result
}

// Frequency count each character, using ETAOINSHRDLU using 12 -> 1 as the score, with all others being 0
// choose the one with the highest value
fn letter_score(letter: u8) -> i32 {
    let c = char::from_u32(u32::from(letter)).unwrap();
    match c {
        ' ' => 1,
        'e' => 12,
    //    'E' => 12,
     //   'T' => 11,
        't' => 11,
        'a' => 10,
     //   'A' => 10,
      //  'O' => 9,
        'o' => 9,
   //     'I' => 8,
        'i' => 8,
   //     'N' => 7,
        'n' => 7,
   //     'S' => 6,
        's' => 6,
  //      'H' => 5,
        'h' => 5,
  //      'R' => 4,
        'r' => 4,
  //      'D' => 3,
        'd' => 3,
   //     'L' => 2,
        'l' => 1,
   //     'U' => 2,
        'u' => 1,
        /*
        '#' => -2,
        '@' => -2,
        '{' => -10,
        '}' => -10,
        '`' => -10,
        '~' => -10,
        */
         _ => 0,
    }
}

fn decrypt_xor(input: &Vec<u8>) -> (char, i32, String) {

    let mut current_candidate = String::from("");
    let mut encoder: char = ' ';
    let mut current_high_score: i32 =  -1000;
    //for &c in ASCII_CHARACTER.iter() {
    for c  in 0..=255 {
        let mut decoded: Vec<u8> = Vec::new();
        let mut abort = false;
        let mut score: i32 = 0;
        for &v in input.iter() {
            let r = c ^ v;
            if !is_ascii(r) {
                abort = true;
                break;
            }
            decoded.push(r);
            score += letter_score(r);
        }
        if !abort {
            if score > current_high_score {
                encoder = char::from_u32(u32::from(c)).unwrap();
                current_high_score = score;
                current_candidate = String::from_utf8(decoded.to_vec()).unwrap();
            }
        }
    }
    (encoder, current_high_score, current_candidate)
}

fn set_1_challenge_4() {
    // load s1p4.txt
    // for each line, run through decoder,
    // check score against current high score, if it wins, save it off
    let mut high_score = -1;
    let mut winning_input: &str = "";
    let mut winning_output = "".to_string();
    let mut encoder = ' ';
    let contents = fs::read_to_string("./s1p4.txt");
    if let Ok(file_contents) = contents {
        for line in file_contents.lines() {
            let decoded = decode_hex(&String::from(line.trim()));
            println!("Input {0}", line);
            let (enc, score, candidate) = decrypt_xor(&decoded);
            if score > high_score {
                println!("{0}: {1}", score, candidate);
                encoder = enc;
                high_score = score;
                winning_output = candidate;
                winning_input = line;
            }
        }
        println!("winner: {0}: {1}", high_score, winning_output);
    } else {
        panic!("Invalid file?");

    }
}

fn main() {
    let mut buffer = String::new();
    let _ = io::stdin().read_line(&mut buffer);
    let result = base64_encode(&buffer.into_bytes());
    if let Ok(s) = String::from_utf8(result) {
        println!("{s}");
    } else {
        println!("Unable to encode");
    }

}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn set_1_challenge_1() {
        let input = String::from("I'm killing your brain like a poisonous mushroom").into_bytes();
        let result = base64_encode(&input);
        if let Ok(r) = String::from_utf8(result) {
            assert_eq!(r, String::from("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"));
        } else {
            assert!(false);
        }
    }

    #[test]
    fn verify_padded_encoding_2() {
        let input = String::from("food").into_bytes();
        let result = base64_encode(&input);
        if let Ok(r) = String::from_utf8(result) {
            assert_eq!(r, String::from("Zm9vZA=="));
        } else {
            assert!(false);
        }
    }

    #[test]
    fn verify_padded_encoding_1() {
        let input = String::from("foodz").into_bytes();
        let result = base64_encode(&input);
        if let Ok(r) = String::from_utf8(result) {
            assert_eq!(r, String::from("Zm9vZHo="));
        } else {
            assert!(false);
        }
    }

    #[test]
    fn verify_decode_hex() {
        
        let b1 = decode_hex(&String::from("010203040506070809"));
        assert_eq!(b1, Vec::from([1,2,3,4,5,6,7,8,9]));
        
        let b2 = decode_hex(&String::from("FF0A0D"));
        assert_eq!(b2, Vec::from([255, 10, 13]));
    }

    #[test]
    fn verify_encode_hex() {
        let s1 = encode_hex(&Vec::from([10,11,255,1]));
        assert_eq!(s1, "0a0bff01");
    }

    #[test]
    fn set_1_challenge_2() {
        let b1 = decode_hex(&String::from("1c0111001f010100061a024b53535009181c"));
        let b2 = decode_hex(&String::from("686974207468652062756c6c277320657965"));
        let r = xor(&b1, &b2);
        assert_eq!(encode_hex(&r), String::from("746865206b696420646f6e277420706c6179"));
    }

    #[test]
    fn set_1_challenge_3() {
        let (_, score, out) = decrypt_xor(&decode_hex(&String::from("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736")));
        println!("{0}: {1}", score, out);
    }

    #[test]
    fn set_1_challenge_4_test() {
        set_1_challenge_4();
    }
}