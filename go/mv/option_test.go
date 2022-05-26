package main

import "testing"

var (
	falsePtr    *bool
	tmpBool     = true
	truePtr     = &tmpBool
	emptyStrPtr *string
	tmpStr      = "string"
	strPtr      = &tmpStr
)

func Test_v_isV(t *testing.T) {
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
			v := &v{
				bool: tt.fields.bool,
			}
			if got := v.isV(); got != tt.want {
				t.Errorf("isV() = %v, want %v", got, tt.want)
			}
		})
	}
}

func Test_option_isValid(t *testing.T) {
	tests := []struct {
		name   string
		option *option
		want   bool
	}{
		{
			name:   "option is nil",
			option: nil,
			want:   false,
		},
		{
			name: "dst is nil",
			option: &option{
				dst: dst{
					string: nil,
				},
				src: src{
					string: strPtr,
				},
			},
			want: false,
		},
		{
			name: "src is nil",
			option: &option{
				dst: dst{
					string: strPtr,
				},
				src: src{
					string: nil,
				},
			},
			want: false,
		},
		{
			name: "dst is empty ptr",
			option: &option{
				dst: dst{
					string: emptyStrPtr,
				},
				src: src{
					string: strPtr,
				},
			},
			want: false,
		},
		{
			name: "src is empty ptr",
			option: &option{
				dst: dst{
					string: strPtr,
				},
				src: src{
					string: emptyStrPtr,
				},
			},
			want: false,
		},
		{
			name: "v is false ptr",
			option: &option{
				dst: dst{},
				src: src{},
				v: v{
					bool: falsePtr,
				},
			},
			want: false,
		},
		{
			name: "v is true ptr",
			option: &option{
				dst: dst{},
				src: src{},
				v: v{
					bool: truePtr,
				},
			},
			want: false,
		},
		{
			name: "all set",
			option: &option{
				dst: dst{
					string: strPtr,
				},
				src: src{
					string: strPtr,
				},
				v: v{
					bool: falsePtr,
				},
			},
			want: true,
		},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := tt.option.isValid(); got != tt.want {
				t.Errorf("isValid() = %v, want %v", got, tt.want)
			}
		})
	}
}
