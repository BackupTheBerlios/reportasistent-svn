<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:param name="params"/>

<xsl:variable name="paramsroot" select="document($params)"/>
<xsl:variable name="mnroot" select="document(string($paramsroot//param[@name='mn']/@value))"/>
<xsl:variable name="mvroot" select="document(string($paramsroot//param[@name='mv']/@value))"/>


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


<xsl:template match="word">
  <xsl:choose>
    <xsl:when test="@class='nominal'">
    <xsl:choose>
        <xsl:when test="@case!='' and @number!=''">
	  		<xsl:call-template name="printnominal">
	    		<xsl:with-param name="case" select="@case"/>
	    		<xsl:with-param name="number" select="@number"/>
	    		<xsl:with-param name="word" select="."/>
	  		</xsl:call-template>
        </xsl:when>
		<xsl:when test="@case!=''">
	  		<xsl:call-template name="printnominal">
	    		<xsl:with-param name="case" select="@case"/>
	    		<xsl:with-param name="number" select="'sg'"/>
	    		<xsl:with-param name="word" select="."/>
	  		</xsl:call-template>
		</xsl:when>
		<xsl:when test="@number!=''">
	  		<xsl:variable name="pattern.name" select="@pattern"/>
	  		<xsl:call-template name="printnominal">
	    		<!--xsl:with-param name="case" select="'1'"/-->
	    		<xsl:with-param name="case" select="$mnroot//pattern[@name=$pattern.name]/endsegment/@case[1]"/>
	    		<xsl:with-param name="number" select="@number"/>
	    		<xsl:with-param name="word" select="."/>
	  		</xsl:call-template>
		</xsl:when>
		<xsl:otherwise>
	 		<!--xsl:text> </xsl:text-->
	 		<xsl:value-of select="text()"/>
	 		<!--xsl:text> </xsl:text-->
    	</xsl:otherwise>
    </xsl:choose>
    </xsl:when>
    
    <xsl:when test="@class='verb'">
      <xsl:choose>
        <xsl:when test="@number = 'pl'">
	  <xsl:call-template name="printverb">
	    <xsl:with-param name="word" select="."/>
	  </xsl:call-template>
	</xsl:when>
	<xsl:when test="@number = 'qpl'">
	  <xsl:call-template name="printverb">
	    <xsl:with-param name="word" select="."/>
	  </xsl:call-template>
	</xsl:when>
	<xsl:otherwise>
	  <!--xsl:text> </xsl:text-->
	  <xsl:value-of select="text()"/>
	  <!--xsl:text> </xsl:text-->
        </xsl:otherwise>
      </xsl:choose>
    </xsl:when>
  </xsl:choose>
</xsl:template>


<xsl:template name="printnominal">
  <xsl:param name="word"/>
  <xsl:param name="case"/>
  <xsl:param name="number"/>
  <xsl:variable name="patternname" select="@pattern"/>
  <xsl:variable name="path" select="$mnroot//pattern[@name=$patternname]"/>
  <!--xsl:variable name="end" select="$path//endsegment[@case='1' and @number='sg']/text()"/-->
  <xsl:variable name="end" select="$path//endsegment[1]/text()"/>
  <xsl:variable name="newend1" select="$path//endsegment[@case=$case and @number=$number]"/>
  <xsl:variable name="newend2" select="$path//endsegment[@number=$number]"/>
  <xsl:variable name="tolength" select="string-length(.) - string-length($end)"/>

   <xsl:choose>
        <xsl:when test="@case!=''">
  			<xsl:value-of select="concat(substring(., 1, $tolength), $newend1)"/>
		</xsl:when>
		<xsl:otherwise>
			<xsl:value-of select="concat(substring(., 1, $tolength), $newend2)"/>
		</xsl:otherwise>
	</xsl:choose>
</xsl:template>


<xsl:template name="printverb">
  <xsl:param name="word"/>
  <xsl:variable name="name" select="@number"/>
  <xsl:variable name="patternname" select="@pattern"/>
  <xsl:variable name="path" select="$mvroot//pattern[@name=$patternname]"/>
  <xsl:choose>
    <xsl:when test="@number = 'pl'">
      <xsl:variable name="end" select="$path//base"/>
      <xsl:variable name="newend" select="$path//pl"/>
      <xsl:variable name="tolength" select="string-length(.) - string-length($end)"/>
      
      <!--xsl:text> </xsl:text-->
      <xsl:value-of select="concat(substring(., 1, $tolength), $newend)"/>
      <!--xsl:text> </xsl:text-->
    </xsl:when>
    <xsl:when test="@number = 'qpl'">
      <xsl:variable name="end" select="$path//base"/>
      <xsl:variable name="newend" select="$path//qpl"/>
      <xsl:variable name="tolength" select="string-length(.) - string-length($end)"/>
      
      <!--xsl:text> </xsl:text-->
      <xsl:value-of select="concat(substring(., 1, $tolength), $newend)"/>
      <!--xsl:text> </xsl:text-->
    </xsl:when>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>