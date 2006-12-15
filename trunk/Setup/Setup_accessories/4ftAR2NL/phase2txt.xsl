<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:output method="text" encoding="windows-1250"/>


<xsl:template match="/sentences">
  
  <xsl:apply-templates/>
  
</xsl:template>


<xsl:template match="sentence">
  <xsl:number format="1. "/>
  <xsl:apply-templates/><xsl:text>&#010;&#010;</xsl:text>
</xsl:template>

<xsl:template match="text()">
  <xsl:value-of select="."/>
</xsl:template>

<xsl:template match="*">
  <xsl:text>&lt;</xsl:text>
    <xsl:value-of select="name()"/>
  <xsl:text>&gt;</xsl:text>
  <xsl:apply-templates/>
</xsl:template>

</xsl:stylesheet>