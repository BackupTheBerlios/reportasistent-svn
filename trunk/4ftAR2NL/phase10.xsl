<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="mvroot" select="document(string($paramsroot//param[@name='mv']/@value))"/>
<xsl:variable name="entityroot" select="document(string($paramsroot//param[@name='entity']/@value))"/>


<xsl:template match="/sentences">
  <sentences>
    <xsl:apply-templates/>
  </sentences>
</xsl:template>


<xsl:template match="sentence">
  <sentence>
    <xsl:apply-templates/>
  </sentence>
</xsl:template>


<xsl:template match="*">
  <xsl:copy-of select="."/>
</xsl:template>


<xsl:template match="floatslot">
  <xsl:variable name="id" select="@id"/>
  <xsl:variable name="role" select="@role"/>
  <xsl:variable name="occno" select="@occno"/>
  <xsl:copy-of select="preceding-sibling::float[@id=$id and @role=$role and @occno=$occno]/node()"/>
  <xsl:copy-of select="following-sibling::float[@id=$id and @role=$role and @occno=$occno]/node()"/>
</xsl:template>


<xsl:template match="float">
  <xsl:variable name="id" select="@id"/>
  <xsl:variable name="role" select="@role"/>
  <xsl:variable name="occno" select="@occno"/>
  <xsl:choose>
    <xsl:when test="preceding-sibling::floatslot[@id=$id and @role=$role and @occno=$occno]"/>
    <xsl:when test="following-sibling::floatslot[@id=$id and @role=$role and @occno=$occno]"/>
    <xsl:otherwise>
      <xsl:value-of select="."/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<xsl:template match="word">
  <xsl:choose>
    <xsl:when test="@class='verb' and @vderivation='ptc'">
      <xsl:variable name="patternname" select="@pattern"/>
      <word>
	<xsl:if test="@case">
	  <xsl:attribute name="case">
	    <xsl:value-of select="@case"/>
	  </xsl:attribute>
	</xsl:if>
	<xsl:if test="@number">
	  <xsl:attribute name="number">
	    <xsl:value-of select="@number"/>
	  </xsl:attribute>
	</xsl:if>
	<xsl:attribute name="class">nominal</xsl:attribute>
	<xsl:if test="$mvroot//pattern[@name=$patternname]/ptcpattern != ''">
	  <xsl:attribute name="pattern">
	    <xsl:value-of select="concat($mvroot//pattern[@name=$patternname]/ptcpattern,
	    				   $entityroot//enamedata[@symbol='EPtcPatternSuffix'])"/>
	  </xsl:attribute>
	</xsl:if>
	
	<xsl:call-template name="printverb">
	  <xsl:with-param name="word" select="."/>
	</xsl:call-template>
      </word>
    </xsl:when>
    <xsl:otherwise>
      <xsl:copy-of select="."/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<xsl:template name="printverb">
  <xsl:param name="word"/>
  <xsl:variable name="patternname" select="@pattern"/>
  <xsl:variable name="path" select="$mvroot//pattern[@name=$patternname]"/>
  
  <xsl:variable name="end" select="$path//base"/>
  <xsl:variable name="newend" select="$path//ptc"/>
  <xsl:variable name="tolength" select="string-length(.) - string-length($end)"/>
  
  <xsl:value-of select="concat(substring(., 1, $tolength), $newend)"/>
</xsl:template>


</xsl:stylesheet>