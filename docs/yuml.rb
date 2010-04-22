#!/usr/bin/env ruby

require 'net/http'

host = "yuml.me"
path = "/diagram/dir:td;scruffy/activity/"
data = ""
open(ARGV[0]) do |yuml_file|
  data = yuml_file.lines.collect{ |line|
    line.strip unless line =~ /^#/
  }.compact.join(", ")
end

open(ARGV[1],'w') do |pict_file|
  pict_file.write Net::HTTP.get(host,URI.escape(path+data))
end