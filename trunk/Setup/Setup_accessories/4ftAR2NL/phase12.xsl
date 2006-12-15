<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:include href="config.xsl"/>

<xsl:output indent="yes" method="xml" encoding="utf-8"/>

<xsl:variable name="paramsroot" select="document(string($params))"/>
<xsl:variable name="langparamroot"
               select="document(string($paramsroot//param[@name='langparam']/@value))"/>
<xsl:variable name="decimal.point.symbol"
               select="$langparamroot//langparam[@name='decimal.point.symbol']/@value"/>

<xsl:template match="/sentences">
<sentences>
  <xsl:apply-templates/>
</sentences>

</xsl:template>


<xsl:template match="sentence">
  <xsl:choose>
    <xsl:when test="$_show = 'correct'">
      <!-- ponechame pouze spravne prevedene sentence -->
      <xsl:if test="boolean(child::literal) = false()">
	<sentence>
	  <xsl:apply-templates/>
	</sentence>
      </xsl:if>
    </xsl:when>
    <xsl:otherwise>
    <!-- zobrazime vsechno -->
      <sentence>
	<xsl:apply-templates/>
      </sentence>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<xsl:template match="*">
  <!--xsl:text>&lt;</xsl:text>
    <xsl:value-of select="name()"/>
  <xsl:text>&gt;</xsl:text-->
  <xsl:copy-of select="."/>
</xsl:template>


<xsl:template match="text()">
  <xsl:call-template name="replace.comma">
    <xsl:with-param name="string" select="normalize-space(.)"/>
  </xsl:call-template>
</xsl:template>


<!-- prevede " , " na ", " -->
<xsl:template name="replace.comma">
  <xsl:param name="string"/>
  
  <xsl:choose>
    <xsl:when test="contains($string, ' , ')">
      <xsl:variable name="rest">
        <xsl:call-template name="replace.comma">
          <xsl:with-param name="string"
	  	select="concat(', ', substring-after($string, ' , '))"/>
        </xsl:call-template>
      </xsl:variable>
      
      <xsl:call-template name="replace.dot">
        <xsl:with-param name="string" 
            select="concat(substring-before($string, ' , '), $rest)"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="replace.dot">
        <xsl:with-param name="string" select="$string"/>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- prevede " ." na "." -->
<xsl:template name="replace.dot">
  <xsl:param name="string"/>
  
  <xsl:choose>
    <xsl:when test="contains($string, ' .')">
      <xsl:variable name="rest">
        <xsl:call-template name="replace.dot">
          <xsl:with-param name="string"
	  	select="concat('. ', substring-after($string, ' .'))"/>
        </xsl:call-template>
      </xsl:variable>
      
      <xsl:call-template name="replace.left.parenthesis">
        <xsl:with-param name="string" 
            select="concat(substring-before($string, ' .'), $rest)"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="replace.left.parenthesis">
        <xsl:with-param name="string" select="$string"/>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- prevede " (" na "(" -->
<xsl:template name="replace.left.parenthesis">
  <xsl:param name="string"/>
  
  <xsl:choose>
    <xsl:when test="contains($string, '( ')">
      <xsl:variable name="rest">
        <xsl:call-template name="replace.left.parenthesis">
          <xsl:with-param name="string"
	  	select="concat('(', substring-after($string, '( '))"/>
        </xsl:call-template>
      </xsl:variable>
      
      <xsl:call-template name="replace.right.parenthesis">
        <xsl:with-param name="string" 
            select="concat(substring-before($string, '( '), $rest)"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="replace.right.parenthesis">
        <xsl:with-param name="string" select="$string"/>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- prevede " )" na ")" -->
<xsl:template name="replace.right.parenthesis">
  <xsl:param name="string"/>
  
  <xsl:choose>
    <xsl:when test="contains($string, ' )')">
      <xsl:variable name="rest">
        <xsl:call-template name="replace.right.parenthesis">
          <xsl:with-param name="string"
	  	select="concat(')', substring-after($string, ' )'))"/>
        </xsl:call-template>
      </xsl:variable>
      
      <xsl:call-template name="decimal.point">
        <xsl:with-param name="string" 
            select="concat(substring-before($string, ' )'), $rest)"/>
	<xsl:with-param name="number" select="0"/>
      </xsl:call-template>
    </xsl:when>
    <xsl:otherwise>
      <xsl:call-template name="decimal.point">
        <xsl:with-param name="string" select="$string"/>
	<xsl:with-param name="number" select="0"/>
      </xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<!-- Prevede desetinou tecku na carku (resp. na symbol v promenne
     $decimal.point.symbol - nekdy to ovsem muze byt naskodu, pokud by napriklad
     cislo bylo casovym udajem a ne desetinym cislem. 
     Promenna $number udava jednociferne cislo, ktere se nachazi v pravo vedle
     desetinne carky. -->
<xsl:template name="decimal.point">
  <xsl:param name="string"/>
  <xsl:param name="number"/>
  
  <xsl:choose>
  
    <xsl:when test="$decimal.point.symbol != '.' and $number &lt; 10">
    
      <xsl:choose>
        <xsl:when test="contains($string, concat('.', string($number)))">
	  <xsl:variable name="rest">
	    <xsl:call-template name="decimal.point">
	      <xsl:with-param name="string"
		    select="concat(concat($decimal.point.symbol, string($number)),
		                    substring-after($string, concat('.', string($number))))"/>
	      <xsl:with-param name="number" select="$number"/>
	    </xsl:call-template>
	  </xsl:variable>
	  <xsl:call-template name="decimal.point">
	    <xsl:with-param name="string" 
		select="concat(substring-before($string, concat('.', string($number))), $rest)"/>
	    <xsl:with-param name="number" select="$number"/>
	  </xsl:call-template>
	</xsl:when>
	
	<xsl:otherwise>
	  <xsl:call-template name="decimal.point">
	    <xsl:with-param name="string" select="$string"/>
	    <xsl:with-param name="number" select="$number + 1"/>
	  </xsl:call-template>
	</xsl:otherwise>
      </xsl:choose>
    
    </xsl:when>
    
    <xsl:otherwise>
      <xsl:call-template name="first.to.upper">
	  <xsl:with-param name="string" select="$string"/>
	</xsl:call-template>
    </xsl:otherwise>
  </xsl:choose>
  
</xsl:template>


<!-- prevede prvni pismeno vety na velke -->
<xsl:template name="first.to.upper">
  <xsl:param name="string"/>
  
  <xsl:choose>
    <!-- chceme pouze prvni pismeno ve vete -->
    <xsl:when test="position() = 1">
  
      <xsl:choose>
	<xsl:when test="starts-with($string, 'a')">
	  <xsl:value-of select="concat('A', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'b')">
	  <xsl:value-of select="concat('B', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'c')">
	  <xsl:value-of select="concat('C', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'č')">
	  <xsl:value-of select="concat('Č', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'd')">
	  <xsl:value-of select="concat('D', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'e')">
	  <xsl:value-of select="concat('E', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'f')">
	  <xsl:value-of select="concat('F', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'g')">
	  <xsl:value-of select="concat('G', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'h')">
	  <xsl:value-of select="concat('H', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'i')">
	  <xsl:value-of select="concat('I', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'j')">
	  <xsl:value-of select="concat('J', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'k')">
	  <xsl:value-of select="concat('K', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'l')">
	  <xsl:value-of select="concat('L', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'm')">
	  <xsl:value-of select="concat('M', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'n')">
	  <xsl:value-of select="concat('N', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'o')">
	  <xsl:value-of select="concat('O', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'p')">
	  <xsl:value-of select="concat('P', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'q')">
	  <xsl:value-of select="concat('Q', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'r')">
	  <xsl:value-of select="concat('R', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'ř')">
	  <xsl:value-of select="concat('Ř', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 's')">
	  <xsl:value-of select="concat('S', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'š')">
	  <xsl:value-of select="concat('Š', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 't')">
	  <xsl:value-of select="concat('T', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'u')">
	  <xsl:value-of select="concat('U', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'ú')">
	  <xsl:value-of select="concat('Ú', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'v')">
	  <xsl:value-of select="concat('V', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'w')">
	  <xsl:value-of select="concat('W', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'x')">
	  <xsl:value-of select="concat('X', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'y')">
	  <xsl:value-of select="concat('Y', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'z')">
	  <xsl:value-of select="concat('Z', substring($string, 2))"/>
	</xsl:when>
	<xsl:when test="starts-with($string, 'ž')">
	  <xsl:value-of select="concat('Ž', substring($string, 2))"/>
	</xsl:when>
	<xsl:otherwise>
	  <xsl:value-of select="$string"/>
	</xsl:otherwise>
      </xsl:choose>
  
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="$string"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


</xsl:stylesheet>