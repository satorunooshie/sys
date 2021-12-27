package main

import (
	"flag"
	"log"
	"os"
	"path/filepath"
)

func main() {
	var opt = newOption()
	flag.Parse()

	if !opt.isValid() {
		log.Fatal("set both src and dst")
	}
	pwd, err := os.Getwd()
	if err != nil {
		log.Fatal(err)
	}
	src := filepath.Join(pwd, *opt.src.string)
	dst := filepath.Join(pwd, *opt.dst.string)
	switch {
	case opt.isV():
		opt.v.run(src, &dst)
	default:
		n := normal{}
		n.run(src, &dst)
	}
}
