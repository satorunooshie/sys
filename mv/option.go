package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"path/filepath"
	"strings"
)

type option struct {
	dst
	src
	v
}

type dst struct {
	*string
}

type src struct {
	*string
}

type v struct {
	*bool
}

type normal struct{}

func (n *normal) run(src string, dst *string) {
	if err := os.Rename(src, *dst); err != nil {
		if _, ok := err.(*os.LinkError); !ok {
			log.Fatal(err)
		}
		// when dst points directory
		if perr := os.Chdir(*dst); perr != nil {
			log.Fatal(err)
		}
		sl := strings.Split(src, "/")
		*dst = filepath.Join(*dst, sl[len(sl)-1])
		if err := os.Rename(src, *dst); err != nil {
			log.Fatal(err)
		}
	}
}

func newOption() *option {
	return &option{
		dst: dst{string: flag.String("dst", "", "destination")},
		src: src{string: flag.String("src", "", "source")},
		v:   v{bool: flag.Bool("v", false, "verbose - print source and destination files")},
	}
}

func (o *option) isValid() bool {
	return o != nil && o.dst.string != nil && o.src.string != nil && strings.TrimSpace(*o.dst.string) != "" && strings.TrimSpace(*o.src.string) != ""
}

func (v *v) isV() bool {
	return v != nil && v.bool != nil && *v.bool
}

func (v *v) run(src string, dst *string) {
	n := normal{}
	n.run(src, dst)
	fmt.Printf("%s -> %s", src, *dst)
}
