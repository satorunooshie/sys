package main

import (
	"testing"
)

var (
	falsePtr *bool
	tmp      = true
	truePtr  = &tmp
)

func Test_a_isA(t *testing.T) {
	type fields struct {
		bool *bool
	}
	tests := []struct {
		name   string
		fields fields
		want   bool
	}{
		{
			name: "false",
			fields: fields{
				bool: falsePtr,
			},
			want: false,
		},
		{
			name: "true",
			fields: fields{
				bool: truePtr,
			},
			want: true,
		},
		{
			name: "nil",
			fields: fields{
				bool: nil,
			},
			want: false,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			a := &a{
				bool: tt.fields.bool,
			}
			if got := a.isA(); got != tt.want {
				t.Errorf("isA() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_t_isT(t1 *testing.T) {
	type fields struct {
		bool *bool
	}
	tests := []struct {
		name   string
		fields fields
		want   bool
	}{
		{
			name: "false",
			fields: fields{
				bool: falsePtr,
			},
			want: false,
		},
		{
			name: "true",
			fields: fields{
				bool: truePtr,
			},
			want: true,
		},
		{
			name: "nil",
			fields: fields{
				bool: nil,
			},
			want: false,
		},
	}
	for _, tt := range tests {
		t1.Run(tt.name, func(t2 *testing.T) {
			t := &t{
				bool: tt.fields.bool,
			}
			if got := t.isT(); got != tt.want {
				t2.Errorf("isT() = %v, want %v", got, tt.want)
			}
		})
	}
}
