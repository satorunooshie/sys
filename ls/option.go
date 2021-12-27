package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"os/user"
	"sort"
	"strconv"
	"strings"
	"syscall"
	"time"

	"github.com/satorunooshie/sys/constants"
)

type option struct {
	a
	t
	l
}

type a struct {
	*bool
}

type t struct {
	*bool
}

type l struct {
	*bool
}

type normal struct{}

func (n *normal) run(fileInfos []os.FileInfo) {
	for _, v := range fileInfos {
		if strings.HasPrefix(v.Name(), ".") {
			continue
		}
		printFileName(v)
	}
}

func newOption() *option {
	return &option{
		a: a{bool: flag.Bool("a", false, "do not ignore entries starting with .")},
		t: t{bool: flag.Bool("t", false, "sort by time, newest first")},
		l: l{bool: flag.Bool("l", false, "use a long listing format")},
	}
}

func (a *a) isA() bool {
	return a != nil && a.bool != nil && *a.bool
}

func (a *a) run(fileInfos []os.FileInfo) {
	for _, v := range fileInfos {
		printFileName(v)
	}
}

func (t *t) isT() bool {
	return t != nil && t.bool != nil && *t.bool
}

func (t *t) run(fileInfos []os.FileInfo) {
	sort.SliceStable(fileInfos, func(i, j int) bool {
		return fileInfos[i].ModTime().After(fileInfos[j].ModTime())
	})
	n := normal{}
	n.run(fileInfos)
}

func (l *l) isL() bool {
	return l != nil && l.bool != nil && *l.bool
}

func (l *l) run(fileInfos []os.FileInfo) {
	type L struct {
		os.FileMode
		HardLinksCount uint64
		OwnerName      string
		GroupName      string
		ByteSize       int64
		TimeStamp      time.Time
		FileName       string
	}
	response := make([]L, len(fileInfos))
	for i, v := range fileInfos {
		response[i].FileMode = v.Mode()
		response[i].TimeStamp = v.ModTime()
		response[i].FileName = v.Name()
		if sys := v.Sys(); sys != nil {
			if stat, ok := sys.(*syscall.Stat_t); ok {
				response[i].ByteSize = stat.Size
				response[i].HardLinksCount = uint64(stat.Nlink)
				uid := strconv.FormatUint(uint64(stat.Uid), 10)
				gid := strconv.FormatUint(uint64(stat.Gid), 10)
				usr, err := user.LookupId(uid)
				if err != nil {
					log.Fatal(err)
				}
				response[i].OwnerName = usr.Name
				group, err := user.LookupGroupId(gid)
				if err != nil {
					log.Fatal(err)
				}
				response[i].GroupName = group.Name
			}
		}
	}
	for _, v := range response {
		s := fmt.Sprintf(
			"%-11v%-5v%-20v%-8v%-5v%-13v%-7v",
			v.FileMode,
			v.HardLinksCount,
			v.OwnerName,
			v.GroupName,
			v.ByteSize,
			v.TimeStamp.Format("Jan 01 15:04"),
			v.FileName,
		)
		fmt.Println(s)
	}
}

func printFileName(v os.FileInfo) {
	if v.IsDir() {
		fmt.Print(constants.Red)
	}
	fmt.Println(v.Name())
	if v.IsDir() {
		fmt.Print(constants.Normal)
	}
}
