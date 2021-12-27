package main

import (
	"flag"
	"io/ioutil"
	"log"
	"os"
)

func main() {
	opt := newOption()
	flag.Parse()

	dir, err := os.Getwd()
	if err != nil {
		log.Fatal(err)
	}
	fileInfos, err := ioutil.ReadDir(dir)
	if err != nil {
		log.Fatal(err)
	}

	switch {
	case opt.isA():
		opt.a.run(fileInfos)
	case opt.isT():
		opt.t.run(fileInfos)
	case opt.isL():
		opt.l.run(fileInfos)
	default:
		n := normal{}
		n.run(fileInfos)
	}
}
